#include "Participant.h"
#include <iostream>

Participant::Participant(std::string name, OrderBook *order_book)
    : name(name), order_book(order_book) {
  Portfolio portfolio;
  std::cout << "Participant " << name << " created" << std::endl;
}

double Participant::check_price(Stock stock) {
  return Participant::order_book->get_price(stock);
}

bool Participant::place_order(int quantity, double price, Stock stock,
                              Side side) {
  Order order(quantity, price, stock, side);
  if (Participant::order_book->place_order(order)) {
    std::cout << Participant::name << " place order" << std::endl;
    pending_orders.push(order);
  } else {
    std::cout << Participant::name << " failed to place order" << std::endl;
    return false;
  }

  return true;
}
