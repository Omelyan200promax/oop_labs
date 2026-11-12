#include "lab2/warehouse/WarehouseMetrics.hpp"

WarehouseMetrics::WarehouseMetrics() : totalBooks_(0), totalOrders_(0) {}

void WarehouseMetrics::addBooks(int count) { totalBooks_ += count; }
void WarehouseMetrics::addOrder() { totalOrders_++; }

int WarehouseMetrics::getAverageBooksPerOrder() const
{
    if (totalOrders_ == 0)
        return 0;
    return totalBooks_ / totalOrders_;
}
