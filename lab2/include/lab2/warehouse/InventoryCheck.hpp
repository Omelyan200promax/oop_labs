#pragma once
#include "lab2/common/CustomDate.hpp"

class InventoryCheck
{
private:
    CustomDate date_;
    bool isCompleted_;

public:
    InventoryCheck(CustomDate date);
    void complete();
    bool isCompleted() const;
};
