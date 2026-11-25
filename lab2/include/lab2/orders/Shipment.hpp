#pragma once
#include "lab2/orders/Order.hpp"
#include "lab2/warehouse/Warehouse.hpp"

class Shipment
{
private:
    Order order_;
    Warehouse warehouse_;

public:
    Shipment(Order order, Warehouse warehouse);
    void ship();
};
