#pragma once

class WarehouseMetrics
{
private:
    int totalBooks_;
    int totalOrders_;

public:
    WarehouseMetrics();
    void addBooks(int count);
    void addOrder();
    int getAverageBooksPerOrder() const;
};
