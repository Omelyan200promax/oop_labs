#pragma once
#include <string>
#include "lab2/common/ContactInfo.hpp"
#include "lab2/common/Address.hpp"
#include "lab2/common/Notification.hpp"
#include <vector>

class Customer
{
private:
    std::string name_;
    ContactInfo contact_;
    Address address_;
    double balance_;
    int activeOrdersCount_ = 0;
    std::vector<Notification> notifications_;
    std::vector<int> orderIds_; // Храним ID заказов, а не сами заказы

public:
    Customer(std::string name, ContactInfo contact, Address address, double balance);
    bool pay(double amount);

    void incrementActiveOrders();
    void decrementActiveOrders();
    void deposit(double amount);

    std::string getName() const;
    std::string getEmail() const;
    std::string getAddressStr() const;
    double getBalance() const;
    int getActiveOrdersCount() const;
    Address getAddress() const;

    void addNotification(const Notification &notif);
    std::vector<Notification> &getNotifications();
    void addOrderId(int orderId);
    std::vector<int> getOrderIds() const;
};
