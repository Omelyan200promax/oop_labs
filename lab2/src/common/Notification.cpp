#include "lab2/common/Notification.hpp"
Notification::Notification(std::string message) : message_(message), isRead_(false) {}
void Notification::markAsRead() { isRead_ = true; }
