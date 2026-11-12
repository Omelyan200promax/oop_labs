#pragma once

class Box
{
private:
    int id_;
    double maxWeight_;
    double currentWeight_;

public:
    Box(int id, double maxWeight);
    bool putBook(double weight);
};
