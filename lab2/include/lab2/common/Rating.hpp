#pragma once

class Rating
{
private:
    double totalScore_;
    int count_;

public:
    Rating();
    void addScore(int score);
    double getScore() const;
};
