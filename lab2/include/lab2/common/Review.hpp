#pragma once
#include <string>
class Review
{
private:
    std::string text_;
    std::string authorName_;

public:
    Review(std::string text, std::string authorName);
    std::string getText() const;
};
