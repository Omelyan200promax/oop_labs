#include "lab2/common/Rating.hpp"

Rating::Rating() : totalScore_(0.0), count_(0) {}

void Rating::addScore(int score)
{
    if (score >= 1 && score <= 5)
    {
        totalScore_ += score;
        count_++;
    }
}

double Rating::getScore() const
{
    if (count_ == 0)
        return 0.0;
    return totalScore_ / count_;
}
