#include "lab2/orders/Delivery.hpp"
#include "lab2/exceptions/DeliveryFailedException.hpp"

Delivery::Delivery(Order order, Address address) : order_(order), address_(address), isDelivered_(false) {}
void Delivery::startDelivery() { order_.changeStatus("In Delivery"); }
void Delivery::completeDelivery()
{
    if (order_.getStatus() != "In Delivery")
    {
        throw DeliveryFailedException("Доставка не была начата");
    }
    isDelivered_ = true;
    order_.changeStatus("Delivered");
}
bool Delivery::isDelivered() const { return isDelivered_; }
