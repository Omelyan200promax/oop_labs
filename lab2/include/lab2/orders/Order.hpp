#pragma once
#include <vector>
#include <string>
#include "lab2/people/Customer.hpp"
#include "lab2/core/Book.hpp"
#include "lab2/common/CustomDate.hpp"

class Order
{
private:
    int id_;
    Customer customer_;
    std::vector<Book> books_;
    CustomDate orderDate_;
    std::string status_;

public:
    Order(int id, Customer customer, CustomDate date);
    void addBook(Book book);
    double calculateTotal() const;
    void changeStatus(std::string newStatus);
    std::string getStatus() const;
    Customer getCustomer() const;
};
