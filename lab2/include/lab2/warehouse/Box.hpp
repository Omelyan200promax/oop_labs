#pragma once
#include <string>
#include <vector>

class Box
{
private:
    int id_;
    double maxWeight_;
    double currentWeight_;
    std::vector<std::string> bookTitles_;
    std::vector<double> bookWeights_;

public:
    Box(int id, double maxWeight);
    bool putBook(double weight, const std::string &title);
    bool removeBook(const std::string &title);
    int countBook(const std::string &title) const;
    int getId() const;
    double getCurrentWeight() const;
    double getMaxWeight() const;
    std::vector<std::string> getContents() const;
};
