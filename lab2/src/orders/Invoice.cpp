#include "lab2/orders/Invoice.hpp"

Invoice::Invoice(int number, Order order) : number_(number), order_(order), totalAmount_(0) {}
void Invoice::generate() { totalAmount_ = order_.calculateTotal(); }
double Invoice::getAmount() const { return totalAmount_; }
