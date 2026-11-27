#pragma once

#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "lab2/common/AuditLog.hpp"
#include "lab2/common/CustomDate.hpp"
#include "lab2/core/Book.hpp"
#include "lab2/orders/Order.hpp"
#include "lab2/orders/ReturnRequest.hpp"
#include "lab2/orders/SupplyContract.hpp"
#include "lab2/people/Accountant.hpp"
#include "lab2/people/Courier.hpp"
#include "lab2/people/Customer.hpp"
#include "lab2/people/Employee.hpp"
#include "lab2/people/SystemUser.hpp"
#include "lab2/warehouse/Equipment.hpp"
#include "lab2/warehouse/Warehouse.hpp"
#include "lab2/warehouse/WarehouseMetrics.hpp"

class Menu
{
private:
    // Заказ + индекс клиента, который его оформил (Order хранит лишь копию клиента)
    struct OrderRecord
    {
        Order order;
        int customerIdx;
    };

    // Запрос клиента на возврат заказа
    struct ReturnRecord
    {
        int orderId;
        std::string reason;
        ReturnRequest request;
        bool processed = false;
    };

    // Договор с поставщиком
    struct SupplyDeal
    {
        std::string supplierName;
        SupplyContract contract;
    };

    std::vector<Book> books_;
    std::vector<Customer> customers_;
    std::vector<OrderRecord> orders_;
    std::vector<std::shared_ptr<Employee>> staff_;
    std::vector<Equipment> equipment_;
    std::vector<SupplyDeal> deals_;
    std::vector<ReturnRecord> returns_;
    std::set<std::pair<int, std::string>> reviewed_; // (клиент, книга), чтобы не оставлять отзыв дважды
    Warehouse warehouse_;
    WarehouseMetrics metrics_;
    AuditLog auditLog_;
    CustomDate today_;
    int nextOrderId_;
    int nextInvoiceId_;
    int nextPaymentId_;
    int activeCustomerIndex_;

    // ----- служебное -----
    void fillWarehouse();
    void logAction(const std::string &text);
    void notifyCustomer(int customerIdx, const std::string &text);
    void requireLevel(const SystemUser &user, int level, const std::string &what) const;
    OrderRecord *findOrder(int orderId);
    Book *findBook(const std::string &title);
    int reservedCopies(const std::string &title) const;
    Equipment *findEquipment(const std::string &name);
    std::vector<int> listOrdersByStatus(const std::string &status);
    std::vector<size_t> showBooks(bool sortByStock) const;

    // ----- главное меню и каталог (menu.cpp) -----
    void runCatalogMenu() const;
    void searchBooks() const;
    void findByIsbn() const;
    void showBookDetails() const;

    // ----- клиент (menu_customer.cpp) -----
    void showCustomers() const;
    void loginCustomer();
    void runCustomerMenu();
    void createOrder();
    void payOrder(OrderRecord &rec);
    void payOrderMenu();
    void cancelOrderMenu();
    void showMyOrders() const;
    void requestReturn();
    void leaveReview();
    void showMyNotifications();

    // ----- сотрудники (menu_staff.cpp) -----
    void loginEmployee();
    void runEmployeeMenu(Employee &emp);
    // действия по ролям
    void managerReport();
    void managerHandleReturns();
    bool managerDiscount();
    void showSupplyDeals() const;
    bool storekeeperReceiveSupply();
    void storekeeperShipOrder();
    void storekeeperWriteOff();
    void courierDeliver(Courier &courier);
    void courierReportBreakdown();
    void accountantPayroll(Accountant &accountant);
    void accountantInvoice();
    void accountantPenalty();
    void editorAddBook();

    // ----- склад (menu_warehouse.cpp) -----
    void runWarehouseMenu();
    void showWarehouseStructure() const;
    void runInventory();
    void manageEquipment();
    void showMetrics() const;

public:
    Menu();
    void run();
};
