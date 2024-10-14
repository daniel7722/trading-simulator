#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include "Data.h"
#include "Order.h"
#include "OrderBook.h"
#include "Portfolio.h"
#include <queue>
#include <string>

class Participant {
private:
  int id;
  std::string name;
  Portfolio portfolio;
  OrderBook *order_book;
  std::queue<Order> pending_orders;

public:
  Participant(std::string name, OrderBook *order_book);

  /**
   * @brief View the portfolio of the participant
   */
  Portfolio const view_portfolio();

  /**
   * @brief Get the current price of a stock
   *
   * @param stock The stock to get the price of
   * @return double The current price of the stock
   */
  double check_price(Stock stock);

  /**
   * @brief Place an order to buy or sell a stock
   *
   * @param quantity The quantity of the stock to buy or sell
   * @param price The price to buy or sell the stock at
   * @param order The order to place
   * @return true The order was placed successfully
   * @return false The order was not placed successfully
   */
  bool place_order(int quantity, double price, Stock stock, Side side);
};

#endif // PARTICIPANT_H