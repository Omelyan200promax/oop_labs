#pragma once
#include <string>
class Report
{
private:
    std::string title_;
    std::string content_;

public:
    Report(std::string title);
    void setContent(std::string content);
    std::string getTitle() const;
};
