#include "menu.hpp"
#include "menu_utils.hpp"

#include <functional>
#include <iostream>
#include <map>
#include <sstream>

#include "lab2/common/Discount.hpp"
#include "lab2/common/Notification.hpp"
#include "lab2/common/Report.hpp"
#include "lab2/core/Author.hpp"
#include "lab2/core/Category.hpp"
#include "lab2/core/CoverType.hpp"
#include "lab2/core/Genre.hpp"
#include "lab2/core/Language.hpp"
#include "lab2/core/Publisher.hpp"
#include "lab2/exceptions/AccessDeniedException.hpp"
#include "lab2/exceptions/CapacityExceededException.hpp"
#include "lab2/exceptions/DeliveryFailedException.hpp"
#include "lab2/exceptions/InvalidBookDataException.hpp"
#include "lab2/exceptions/OutOfStockException.hpp"
#include "lab2/exceptions/SupplierNotFoundException.hpp"
#include "lab2/exceptions/WarehouseException.hpp"
#include "lab2/orders/Delivery.hpp"
#include "lab2/orders/Invoice.hpp"
#include "lab2/orders/Penalty.hpp"
#include "lab2/orders/Refund.hpp"
#include "lab2/orders/Shipment.hpp"
#include "lab2/people/Accountant.hpp"
#include "lab2/people/Auditor.hpp"
#include "lab2/people/Courier.hpp"
#include "lab2/people/Editor.hpp"
#include "lab2/people/Manager.hpp"
#include "lab2/people/Storekeeper.hpp"

namespace
{
    struct Action
    {
        std::string title;
        std::function<void()> run;
    };
}

// ===================== вход сотрудника =====================

void Menu::loginEmployee()
{
    std::cout << "\nВыберите сотрудника:\n";
    for (size_t i = 0; i < staff_.size(); ++i)
        std::cout << i + 1 << ". " << ui::pad(staff_[i]->getName(), 20) << ui::pad(staff_[i]->getRole().getTitle(), 11)
                  << "(уровень доступа " << staff_[i]->getRole().getAccessLevel() << ")\n";
    std::cout << "0. Назад\n\nВыбор: ";
    int idx = ui::readInt(0, static_cast<int>(staff_.size()));
    if (idx == 0)
        return;
    runEmployeeMenu(*staff_[idx - 1]);
}

// Меню строится из списка действий: общие для всех + зависящие от конкретного класса сотрудника.
void Menu::runEmployeeMenu(Employee &emp)
{
    SystemUser user(emp.getName(), emp.getRole()); // проверка уровня доступа идёт через роль
    const int level = emp.getRole().getAccessLevel();

    std::vector<Action> actions;
    actions.push_back({"Выполнить работу", [&]
                       { emp.work(); }});
    actions.push_back({"Журнал действий системы (нужен уровень 4+)", [&]
                       {
                           requireLevel(user, 4, "просмотр журнала");
                           std::cout << "\n--- Журнал действий ---\n";
                           auditLog_.printLog();
                       }});

    if (auto *m = dynamic_cast<Manager *>(&emp))
    {
        actions.push_back({"Сформировать отчёт по продажам", [&, m]
                           {
                               requireLevel(user, 4, "отчёт");
                               m->createReport();
                               managerReport();
                           }});
        actions.push_back({"Обработать запросы на возврат", [&]
                           {
                               requireLevel(user, 5, "обработка возвратов");
                               managerHandleReturns();
                           }});
        actions.push_back({"Назначить скидку на книгу", [&, m]
                           {
                               requireLevel(user, 5, "назначение скидки");
                               if (managerDiscount())
                                   m->applyDiscountToBook();
                           }});
        actions.push_back({"Договоры с поставщиками", [&]
                           { showSupplyDeals(); }});
        actions.push_back({"Метрики склада", [&]
                           { showMetrics(); }});
    }
    else if (auto *s = dynamic_cast<Storekeeper *>(&emp))
    {
        actions.push_back({"Принять поставку от поставщика", [&, s]
                           {
                               requireLevel(user, 3, "приёмка поставки");
                               if (storekeeperReceiveSupply())
                                   s->sortBooks();
                           }});
        actions.push_back({"Отгрузить оплаченный заказ", [&]
                           {
                               requireLevel(user, 3, "отгрузка");
                               storekeeperShipOrder();
                           }});
        actions.push_back({"Списать потерянную книгу с полки", [&]
                           {
                               requireLevel(user, 3, "списание");
                               storekeeperWriteOff();
                           }});
        actions.push_back({"Структура склада", [&]
                           { showWarehouseStructure(); }});
        actions.push_back({"Оборудование (проверка и ремонт)", [&]
                           { manageEquipment(); }});
    }
    else if (auto *c = dynamic_cast<Courier *>(&emp))
    {
        actions.push_back({"Доставить заказ", [&, c]
                           {
                               requireLevel(user, 2, "доставка");
                               courierDeliver(*c);
                           }});
        actions.push_back({"Сообщить о поломке фургона", [&]
                           { courierReportBreakdown(); }});
    }
    else if (auto *a = dynamic_cast<Auditor *>(&emp))
    {
        actions.push_back({"Провести инвентаризацию", [&, a]
                           {
                               requireLevel(user, 4, "инвентаризация");
                               a->checkInventory();
                               runInventory();
                           }});
        actions.push_back({"Метрики склада", [&]
                           { showMetrics(); }});
        actions.push_back({"Структура склада", [&]
                           { showWarehouseStructure(); }});
    }
    else if (auto *acc = dynamic_cast<Accountant *>(&emp))
    {
        actions.push_back({"Начислить зарплату всем сотрудникам", [&, acc]
                           {
                               requireLevel(user, 4, "начисление зарплаты");
                               accountantPayroll(*acc);
                           }});
        actions.push_back({"Выставить счёт по заказу", [&]
                           {
                               requireLevel(user, 4, "выставление счёта");
                               accountantInvoice();
                           }});
        actions.push_back({"Оформить штраф сотруднику", [&]
                           {
                               requireLevel(user, 4, "штраф");
                               accountantPenalty();
                           }});
    }
    else if (auto *e = dynamic_cast<Editor *>(&emp))
    {
        actions.push_back({"Редактировать описание книги", [&, e]
                           {
                               requireLevel(user, 3, "редактирование");
                               e->editBook();
                           }});
        actions.push_back({"Добавить новую книгу в каталог", [&]
                           {
                               requireLevel(user, 3, "добавление книги");
                               editorAddBook();
                           }});
    }

    int choice;
    do
    {
        std::cout << "\n=== " << emp.getName() << " — " << emp.getRole().getTitle() << " (уровень " << level << ") ===\n";
        for (size_t i = 0; i < actions.size(); ++i)
            std::cout << i + 1 << ". " << actions[i].title << "\n";
        std::cout << "0. Выйти\n\nВыбор: ";
        choice = ui::readInt(0, static_cast<int>(actions.size()));
        if (choice == 0)
            break;
        try
        {
            actions[choice - 1].run();
        }
        catch (const std::exception &ex) // WarehouseException и все его наследники, invalid_argument и т.д.
        {
            std::cout << "ОШИБКА: " << ex.what() << "\n";
        }
    } while (true);
}

// ===================== менеджер =====================

void Menu::managerReport()
{
    std::map<std::string, int> byStatus;
    double revenue = 0;
    for (const auto &rec : orders_)
    {
        byStatus[rec.order.getStatus()]++;
        const std::string st = rec.order.getStatus();
        if (st == "Paid" || st == "Shipped" || st == "In Delivery" || st == "Delivered")
            revenue += rec.order.calculateTotal();
    }
    std::ostringstream os;
    os << "Всего заказов: " << orders_.size() << "\n";
    for (const auto &entry : byStatus)
        os << "  " << ui::statusRu(entry.first) << ": " << entry.second << "\n";
    os << "Выручка (оплаченные заказы без возвратов и отмен): " << ui::money(revenue) << " BYN\n"
       << "Среднее число книг в заказе: " << metrics_.getAverageBooksPerOrder() << "\n"
       << "Запросов на возврат: " << returns_.size();

    Report report("Отчёт по продажам на " + today_.toString());
    report.setContent(os.str());
    std::cout << "\n=== " << report.getTitle() << " ===\n" << report.getContent() << "\n";
    logAction("Сформирован отчёт по продажам");
}

void Menu::managerHandleReturns()
{
    std::vector<size_t> pending;
    for (size_t i = 0; i < returns_.size(); ++i)
        if (!returns_[i].processed)
            pending.push_back(i);
    if (pending.empty())
    {
        std::cout << "Нет необработанных запросов на возврат.\n";
        return;
    }
    std::cout << "\nЗапросы на возврат:\n";
    for (size_t i = 0; i < pending.size(); ++i)
    {
        const auto &rr = returns_[pending[i]];
        OrderRecord *rec = findOrder(rr.orderId);
        std::cout << i + 1 << ". Заказ №" << rr.orderId << " (" << customers_[rec->customerIdx].getName()
                  << ", " << ui::money(rec->order.calculateTotal()) << " BYN). Причина: " << rr.reason << "\n";
    }
    std::cout << "Выберите запрос (0 - назад): ";
    int n = ui::readInt(0, static_cast<int>(pending.size()));
    if (n == 0)
        return;

    ReturnRecord &rr = returns_[pending[n - 1]];
    OrderRecord *rec = findOrder(rr.orderId);
    std::cout << "1 - одобрить и вернуть деньги, 2 - отклонить, 0 - отмена: ";
    int decision = ui::readInt(0, 2);
    if (decision == 0)
        return;

    if (decision == 1)
    {
        rr.request.approve();
        Refund refund(rr.request, Price(rec->order.calculateTotal(), "BYN"));
        refund.processRefund(); // бросит InvalidOrderException, если возврат не одобрен
        customers_[rec->customerIdx].deposit(refund.getAmount());
        for (const auto &title : rec->order.getBookTitles())
        {
            if (Book *b = findBook(title))
            {
                b->addStock(1);
                warehouse_.storeBook(b->getWeight(), title); // книга возвращается на полку
            }
        }
        rec->order.changeStatus("Returned");
        notifyCustomer(rec->customerIdx, "Возврат по заказу №" + std::to_string(rr.orderId) + " одобрен, " + ui::money(refund.getAmount()) + " BYN возвращено на баланс");
        logAction("Одобрен возврат по заказу №" + std::to_string(rr.orderId));
        std::cout << "Возврат одобрен: " << ui::money(refund.getAmount()) << " BYN возвращено клиенту, книги вернулись на склад.\n";
    }
    else
    {
        notifyCustomer(rec->customerIdx, "Возврат по заказу №" + std::to_string(rr.orderId) + " отклонён");
        logAction("Отклонён возврат по заказу №" + std::to_string(rr.orderId));
        std::cout << "Запрос отклонён, клиент уведомлён.\n";
    }
    rr.processed = true;
}

bool Menu::managerDiscount()
{
    auto map = showBooks(false);
    std::cout << "Выберите книгу (0 - отмена): ";
    int n = ui::readInt(0, static_cast<int>(map.size()));
    if (n == 0)
        return false;
    Book &b = books_[map[n - 1]];
    std::cout << "Скидка, % (1-90): ";
    int percent = ui::readInt(1, 90);
    Discount promo("Акция менеджера", percent);
    double before = b.getPriceAmount();
    double after = promo.apply(before);
    b.applyDiscount(percent);
    logAction("Скидка " + std::to_string(percent) + "% на \"" + b.getTitle() + "\"");
    std::cout << "Цена \"" << b.getTitle() << "\": " << ui::money(before) << " -> " << ui::money(after)
              << " BYN (сейчас в каталоге " << ui::money(b.getPriceAmount()) << " BYN)\n";
    return true;
}

void Menu::showSupplyDeals() const
{
    std::cout << "\nДоговоры поставки:\n";
    for (const auto &d : deals_)
        std::cout << "  " << ui::pad(d.supplierName, 22) << "действует до " << d.contract.getEndDate().toString()
                  << " — " << (d.contract.isActive(today_) ? "АКТИВЕН" : "ИСТЁК") << "\n";
}

// ===================== кладовщик =====================

bool Menu::storekeeperReceiveSupply()
{
    showSupplyDeals();
    std::cout << "\nВыберите поставщика:\n";
    for (size_t i = 0; i < deals_.size(); ++i)
        std::cout << i + 1 << ". " << deals_[i].supplierName << "\n";
    std::cout << "0. Назад\n\nВыбор: ";
    int d = ui::readInt(0, static_cast<int>(deals_.size()));
    if (d == 0)
        return false;
    SupplyDeal &deal = deals_[d - 1];
    if (!deal.contract.isActive(today_))
        throw SupplierNotFoundException("Нет действующего договора с поставщиком " + deal.supplierName);

    auto map = showBooks(false);
    std::cout << "Какую книгу привезли (0 - отмена): ";
    int n = ui::readInt(0, static_cast<int>(map.size()));
    if (n == 0)
        return false;
    Book &book = books_[map[n - 1]];
    std::cout << "Количество (1-100): ";
    int qty = ui::readInt(1, 100);

    int stored = 0;
    while (stored < qty && warehouse_.storeBook(book.getWeight(), book.getTitle()))
        ++stored;
    if (stored > 0)
    {
        deal.contract.getSupplier().supplyBooks(book, stored); // увеличивает остаток в учёте
        logAction("Принята поставка: \"" + book.getTitle() + "\" x" + std::to_string(stored) + " от " + deal.supplierName);
    }
    if (stored < qty)
        throw CapacityExceededException("Не хватило места на складе: принято " + std::to_string(stored) + " из " + std::to_string(qty) + " шт.");
    return true;
}

void Menu::storekeeperShipOrder()
{
    auto ids = listOrdersByStatus("Paid");
    if (ids.empty())
    {
        std::cout << "Нет оплаченных заказов к отгрузке.\n";
        return;
    }
    std::cout << "\nОплаченные заказы:\n";
    for (size_t i = 0; i < ids.size(); ++i)
    {
        OrderRecord *rec = findOrder(ids[i]);
        std::cout << i + 1 << ". Заказ №" << ids[i] << " (" << customers_[rec->customerIdx].getName() << "), книг: " << rec->order.getBookTitles().size() << "\n";
    }
    std::cout << "Выберите заказ (0 - назад): ";
    int n = ui::readInt(0, static_cast<int>(ids.size()));
    if (n == 0)
        return;
    OrderRecord &rec = *findOrder(ids[n - 1]);

    // Сначала проверяем, что все книги физически есть на складе
    std::map<std::string, int> need;
    for (const auto &t : rec.order.getBookTitles())
        need[t]++;
    for (const auto &entry : need)
        if (warehouse_.countBook(entry.first) < entry.second)
            throw OutOfStockException("На складе не найдена книга \"" + entry.first + "\" — отгрузка невозможна");

    Shipment shipment(rec.order, warehouse_);
    shipment.ship(); // Shipment работает с копией заказа, поэтому статус дублируем в реальном заказе
    rec.order.changeStatus("Shipped");
    for (const auto &t : rec.order.getBookTitles())
        warehouse_.removeBook(t);
    notifyCustomer(rec.customerIdx, "Заказ №" + std::to_string(rec.order.getId()) + " отгружен со склада и передан курьеру");
    logAction("Отгружен заказ №" + std::to_string(rec.order.getId()));
    std::cout << "Заказ №" << rec.order.getId() << " отгружен со склада.\n";
}

void Menu::storekeeperWriteOff()
{
    auto map = showBooks(false);
    std::cout << "Какая книга пропала с полки (0 - отмена): ";
    int n = ui::readInt(0, static_cast<int>(map.size()));
    if (n == 0)
        return;
    const std::string title = books_[map[n - 1]].getTitle();
    if (!warehouse_.removeBook(title))
    {
        std::cout << "Такой книги на складе нет.\n";
        return;
    }
    logAction("С полки пропала книга \"" + title + "\" (в учёте не отражено)");
    std::cout << "Книга \"" << title << "\" убрана с полки. В учёте остаток не менялся — расхождение выявит инвентаризация.\n";
}

// ===================== курьер =====================

void Menu::courierDeliver(Courier &courier)
{
    auto ids = listOrdersByStatus("Shipped");
    if (ids.empty())
    {
        std::cout << "Нет отгруженных заказов для доставки.\n";
        return;
    }
    std::cout << "\nЗаказы к доставке:\n";
    for (size_t i = 0; i < ids.size(); ++i)
    {
        OrderRecord *rec = findOrder(ids[i]);
        std::cout << i + 1 << ". Заказ №" << ids[i] << " -> " << customers_[rec->customerIdx].getAddressStr() << "\n";
    }
    std::cout << "Выберите заказ (0 - назад): ";
    int n = ui::readInt(0, static_cast<int>(ids.size()));
    if (n == 0)
        return;
    OrderRecord &rec = *findOrder(ids[n - 1]);

    Equipment *van = findEquipment("Фургон");
    if (van && !van->checkStatus())
        throw DeliveryFailedException("Фургон неисправен, доставка невозможна. Нужен ремонт (кладовщик, раздел «Оборудование»)");

    Delivery delivery(rec.order, customers_[rec.customerIdx].getAddress());
    delivery.startDelivery();
    rec.order.changeStatus("In Delivery");
    courier.deliverOrder();
    delivery.completeDelivery(); // бросит DeliveryFailedException, если доставка не была начата
    rec.order.changeStatus("Delivered");
    customers_[rec.customerIdx].decrementActiveOrders();
    notifyCustomer(rec.customerIdx, "Заказ №" + std::to_string(rec.order.getId()) + " доставлен. Можно оставить отзыв!");
    logAction("Доставлен заказ №" + std::to_string(rec.order.getId()));
    std::cout << "Заказ №" << rec.order.getId() << " доставлен: " << (delivery.isDelivered() ? "да" : "нет") << ".\n";
}

void Menu::courierReportBreakdown()
{
    for (auto &e : equipment_)
    {
        if (e.getName() == "Фургон")
        {
            e = Equipment("Фургон", false);
            logAction("Курьер сообщил о поломке фургона");
            std::cout << "Поломка зарегистрирована. Пока фургон не починят, доставки невозможны.\n";
            return;
        }
    }
}

// ===================== бухгалтер =====================

void Menu::accountantPayroll(Accountant &accountant)
{
    for (auto &emp : staff_)
        accountant.calculateSalary(*emp);
    logAction("Начислена зарплата сотрудникам");
}

void Menu::accountantInvoice()
{
    if (orders_.empty())
    {
        std::cout << "Заказов пока нет.\n";
        return;
    }
    std::cout << "\nЗаказы:\n";
    for (size_t i = 0; i < orders_.size(); ++i)
        std::cout << i + 1 << ". Заказ №" << orders_[i].order.getId() << " — " << ui::statusRu(orders_[i].order.getStatus()) << "\n";
    std::cout << "Выберите заказ (0 - назад): ";
    int n = ui::readInt(0, static_cast<int>(orders_.size()));
    if (n == 0)
        return;
    Invoice invoice(nextInvoiceId_++, orders_[n - 1].order);
    invoice.generate();
    std::cout << "Счёт №" << nextInvoiceId_ - 1 << " по заказу №" << orders_[n - 1].order.getId()
              << " на сумму " << ui::money(invoice.getAmount()) << " BYN выставлен.\n";
    logAction("Выставлен счёт по заказу №" + std::to_string(orders_[n - 1].order.getId()));
}

void Menu::accountantPenalty()
{
    for (size_t i = 0; i < staff_.size(); ++i)
        std::cout << i + 1 << ". " << staff_[i]->getName() << " (" << staff_[i]->getRole().getTitle() << ")\n";
    std::cout << "Кого оштрафовать (0 - отмена): ";
    int n = ui::readInt(0, static_cast<int>(staff_.size()));
    if (n == 0)
        return;
    std::string reason = ui::ask("Причина штрафа: ");
    if (reason.empty())
        reason = "не указана";
    std::cout << "Сумма штрафа, BYN: ";
    double amount = ui::readPositiveDouble();
    Penalty penalty(reason, Price(amount, "BYN"));
    penalty.applyPenalty();
    logAction("Штраф " + ui::money(amount) + " BYN сотруднику " + staff_[n - 1]->getName() + ": " + reason);
    std::cout << "Сотрудник " << staff_[n - 1]->getName() << " оштрафован на " << ui::money(amount) << " BYN.\n";
}

// ===================== редактор =====================

void Menu::editorAddBook()
{
    std::string title = ui::ask("Название: ");
    std::string isbn = ui::ask("ISBN: ");
    std::string first = ui::ask("Имя автора: ");
    std::string last = ui::ask("Фамилия автора: ");
    std::cout << "Цена, BYN: ";
    double price = ui::readPositiveDouble();
    std::string dimLine = ui::ask("Размеры в см (длина ширина высота), например 20 13 3: ");

    double l = 0, w = 0, h = 0;
    std::istringstream dims(ui::lowerUtf8(dimLine));
    dims >> l >> w >> h; // при ошибке остаются нули -> InvalidDimensionsException

    for (const auto &b : books_)
        if (!isbn.empty() && b.getIsbn() == isbn)
            throw InvalidBookDataException("Книга с ISBN " + isbn + " уже есть в каталоге");

    Book book(title, isbn, Author(first, last, "Неизвестно"), Publisher("Не указано", "—"),
              Genre("Не указан", "—"), Category("Новинки", "Новые поступления"), Language("Русский", "ru"),
              CoverType("Мягкая", false), Price(price, "BYN"), Dimensions(l, w, h), today_, 0);
    books_.push_back(book);
    logAction("В каталог добавлена книга \"" + title + "\"");
    std::cout << "Книга добавлена в каталог (остаток 0 — оформите поставку, чтобы она появилась на складе).\n";
}
