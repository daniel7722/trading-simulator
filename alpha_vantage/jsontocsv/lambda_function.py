import json
import boto3

def convert_json_to_dynamodb_format(json_content):
    dynamodb_items = []
    time_series = json_content.get("Time Series (5min)", {})
    for timestamp, data in time_series.items():
        item = {
            "symbol": json_content["Meta Data"]["2. Symbol"],  
            "timestamp": timestamp,
            "open": data.get("1. open"),
            "high": data.get("2. high"),
            "low": data.get("3. low"),
            "close": data.get("4. close"),
            "volume": data.get("5. volume")
        }
        dynamodb_items.append(item)
    return dynamodb_items

def lambda_handler(event, context):
    s3 = boto3.client('s3')
    bucket_name = "dhstockdata"
    raw_data_filepath = "MSFT_data.json"
    response = s3.get_object(Bucket=bucket_name, Key=raw_data_filepath)
    json_content = json.loads(response['Body'].read().decode('utf-8'))
    dynamodb_items = convert_json_to_dynamodb_format(json_content)
    dynamodb = boto3.resource('dynamodb')
    table_name = "stock-data" 
    table = dynamodb.Table(table_name)

    try:
        with table.batch_writer() as batch:
            for item in dynamodb_items:
                batch.put_item(Item=item)
        return {
            'statusCode': 200,
            'body': json.dumps('Successfully inserted JSON data into DynamoDB table!')
        }
    except Exception as e:
        return {
            'statusCode': 500,
            'body': json.dumps(f'Error: {str(e)}')
        }
