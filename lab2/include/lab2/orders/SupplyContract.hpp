#pragma once
#include "lab2/people/Supplier.hpp"
#include "lab2/common/CustomDate.hpp"

class SupplyContract
{
private:
    Supplier supplier_;
    CustomDate startDate_;
    CustomDate endDate_;

public:
    SupplyContract(Supplier supplier, CustomDate start, CustomDate end);
    bool isActive(CustomDate currentDate) const;
    Supplier &getSupplier();
    CustomDate getEndDate() const;
};
