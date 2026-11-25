#include "lab2/orders/SupplyContract.hpp"

SupplyContract::SupplyContract(Supplier supplier, CustomDate start, CustomDate end)
    : supplier_(supplier), startDate_(start), endDate_(end) {}

// Упрощенная проверка (для учебной лабы просто возвращаем true)
bool SupplyContract::isActive(CustomDate currentDate) const
{
    return true;
}
