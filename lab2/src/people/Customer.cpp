#include "lab2/people/Customer.hpp"

Customer::Customer(std::string name, ContactInfo contact, Address address, double balance)
    : name_(name), contact_(contact), address_(address), balance_(balance) {}

bool Customer::pay(double amount)
{
    if (balance_ >= amount)
    {
        balance_ -= amount;
        return true;
    }
    return false;
}

std::string Customer::getName() const { return name_; }
std::string Customer::getEmail() const { return contact_.getEmail(); }
std::string Customer::getAddressStr() const { return address_.getFullAddress(); }
double Customer::getBalance() const { return balance_; }
Address Customer::getAddress() const { return address_; }
int Customer::getActiveOrdersCount() const { return activeOrdersCount_; }

void Customer::incrementActiveOrders() { activeOrdersCount_++; }

void Customer::decrementActiveOrders()
{
    if (activeOrdersCount_ > 0)
        activeOrdersCount_--;
}

void Customer::deposit(double amount)
{
    if (amount > 0)
    {
        balance_ += amount;
    }
}

void Customer::addNotification(const Notification &notif) { notifications_.push_back(notif); }
std::vector<Notification> &Customer::getNotifications() { return notifications_; }
void Customer::addOrderId(int orderId) { orderIds_.push_back(orderId); }
std::vector<int> Customer::getOrderIds() const { return orderIds_; }