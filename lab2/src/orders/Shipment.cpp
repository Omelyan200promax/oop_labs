#include "lab2/orders/Shipment.hpp"

Shipment::Shipment(Order order, Warehouse warehouse) : order_(order), warehouse_(warehouse) {}
void Shipment::ship() { order_.changeStatus("Shipped"); }
