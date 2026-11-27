#pragma once
#include <string>
class Notification
{
private:
    std::string message_;
    bool isRead_;

public:
    Notification(std::string message);
    void markAsRead();
    std::string getMessage() const;
    bool isRead() const;
};
