#include "OrderBook.h"

OrderBook::OrderBook() { book[Stock::AAPL] = 50; };

double OrderBook::get_price(Stock stock) { return book.at(stock); }

bool OrderBook::place_order(Order order) { return true; }
