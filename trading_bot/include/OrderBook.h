#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include "Data.h"
#include "Order.h"
#include <unordered_map>

class OrderBook {
private:
  std::unordered_map<Stock, double> book;

public:
  OrderBook();
  double get_price(Stock stock);
  bool place_order(Order order);
};

#endif // ORDER_BOOK_H