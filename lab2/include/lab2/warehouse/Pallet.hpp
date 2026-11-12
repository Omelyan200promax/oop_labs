#pragma once

class Pallet
{
private:
    int id_;
    int maxBoxes_;
    int currentBoxes_;

public:
    Pallet(int id, int maxBoxes);
    bool addBox();
    int getFreeSpace() const;
};
