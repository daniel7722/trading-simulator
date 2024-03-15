import json
import os
import requests
import boto3

def lambda_handler(event, context):
    try: 
        symbol = event['symbol']
        interval = event['interval']
        API_KEY = os.environ['API_KEY']
        url = f'https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol={symbol}&interval={interval}&apikey={API_KEY}'
        with requests.get(url, stream=True) as response:
            response.raise_for_status() 
            s3 = boto3.client('s3')
            bucket_name = 'dhstockdata'
            timestamp = event.get('timestamp', '')
            object_key = f'{timestamp}_data.json'
            data_bytes = b''
            for chunk in response.iter_content(chunk_size=8192):
                data_bytes += chunk
            s3.put_object(Bucket=bucket_name, Key=object_key, Body=data_bytes)
        return {
            'statusCode': 200,
            'body': json.dumps({
                'message': 'Data uploaded to S3 successfully',
                'bucket': bucket_name,
                'object_key': object_key
            })
        }
    except Exception as e:
        print(f"Error: {str(e)}")
        return {
            'statusCode': 404,
            'body': json.dumps("not successful")
        }