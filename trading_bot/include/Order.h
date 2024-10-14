#ifndef ORDER_H
#define ORDER_H

#include "Data.h"

class Order {
private:
  int quantity;
  double price;
  Stock stock;
  Side side;

public:
  Order(int quantity, double price, Stock stock, Side side);
};

#endif // ORDER_H