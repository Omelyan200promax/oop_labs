#include "lab2/orders/SupplyContract.hpp"

SupplyContract::SupplyContract(Supplier supplier, CustomDate start, CustomDate end)
    : supplier_(supplier), startDate_(start), endDate_(end) {}

// Договор действует, если текущая дата лежит в промежутке [start, end]
bool SupplyContract::isActive(CustomDate currentDate) const
{
    return startDate_ <= currentDate && currentDate <= endDate_;
}

Supplier &SupplyContract::getSupplier() { return supplier_; }
CustomDate SupplyContract::getEndDate() const { return endDate_; }
