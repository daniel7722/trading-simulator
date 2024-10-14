#include "OrderBook.h"
#include "Participant.h"
#include <iostream>

int main() {
  OrderBook *orderbook = new OrderBook();
  Participant alice("Alice", orderbook);
  Participant bob("Bob", orderbook);

  double price = alice.check_price(Stock::AAPL);
  std::cout << "Price of AAPL: " << price << std::endl;
  alice.place_order(10, 100, Stock::AAPL, Side::BUY);

  return 0;
}