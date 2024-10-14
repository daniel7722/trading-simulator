#include "Order.h"

Order::Order(int quantity, double price, Stock stock, Side side)
    : quantity(quantity), price(price), stock(stock), side(side) {}