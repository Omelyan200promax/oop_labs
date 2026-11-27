#include "lab2/orders/Refund.hpp"
#include "lab2/exceptions/InvalidOrderException.hpp"

Refund::Refund(ReturnRequest request, Price amount) : request_(request), amount_(amount) {}
double Refund::getAmount() const { return amount_.getAmount(); }

void Refund::processRefund()
{
    if (!request_.isApproved())
    {
        throw InvalidOrderException("Возврат не одобрен");
    }
}
