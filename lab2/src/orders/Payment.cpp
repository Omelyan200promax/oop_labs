#include "lab2/orders/Payment.hpp"
#include "lab2/exceptions/InvalidPaymentException.hpp"

Payment::Payment(int id, Customer customer, Price amount)
    : id_(id), customer_(customer), amount_(amount), isSuccess_(false) {}

void Payment::processPayment()
{
    if (customer_.pay(1000.0))
    { // Упрощенно
        isSuccess_ = true;
    }
    else
    {
        throw InvalidPaymentException("Недостаточно средств");
    }
}
bool Payment::getStatus() const { return isSuccess_; }
