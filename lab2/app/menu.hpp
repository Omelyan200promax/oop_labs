#pragma once

#include <vector>
#include <string>
#include "lab2/core/Book.hpp"
#include "lab2/people/Customer.hpp"
#include "lab2/orders/Order.hpp"

#pragma once

#include <vector>
#include <memory>
#include <iomanip>
#include "lab2/core/Book.hpp"
#include "lab2/people/Customer.hpp"
#include "lab2/people/Manager.hpp"
#include "lab2/people/Storekeeper.hpp"
#include "lab2/people/Courier.hpp"
#include "lab2/orders/Order.hpp"
#include "lab2/warehouse/Warehouse.hpp"

class Menu
{
private:
    std::vector<Book> books_;
    std::vector<Customer> customers_;
    std::vector<Order> orders_;
    std::vector<std::shared_ptr<Employee>> staff_;
    Warehouse warehouse_;
    int nextOrderId_;

    void showBooks() const;
    void showCustomers() const;
    void showStaff() const;
    void showWarehouse() const;
    void createOrder();
    void payOrder();
    void shipOrder();
    void deliverOrder();
    void leaveReview();
    void showBookDetails() const;
    void showCustomerHistory() const;
    void searchBooks() const;
    void cancelOrder();
    void depositToCustomer();

public:
    Menu();
    void run();
};
