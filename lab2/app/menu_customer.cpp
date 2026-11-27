#include "menu.hpp"
#include "menu_utils.hpp"

#include <algorithm>
#include <iostream>

#include "lab2/common/Notification.hpp"
#include "lab2/common/Review.hpp"
#include "lab2/exceptions/InvalidPaymentException.hpp"
#include "lab2/exceptions/OutOfStockException.hpp"
#include "lab2/orders/Invoice.hpp"
#include "lab2/orders/Payment.hpp"

// ===================== вход клиента =====================

void Menu::showCustomers() const
{
    std::cout << "\nСписок клиентов:\n";
    std::cout << ui::pad("№", 4) << ui::pad("Имя", 22) << ui::pad("Email", 24)
              << ui::pad("Адрес", 34) << "Баланс\n";
    std::cout << std::string(96, '-') << "\n";
    for (size_t i = 0; i < customers_.size(); ++i)
    {
        std::cout << ui::pad(std::to_string(i + 1), 4)
                  << ui::pad(customers_[i].getName(), 22)
                  << ui::pad(customers_[i].getEmail(), 24)
                  << ui::pad(customers_[i].getAddressStr(), 34)
                  << ui::money(customers_[i].getBalance()) << " BYN\n";
    }
}

void Menu::loginCustomer()
{
    showCustomers();
    std::cout << "Выберите клиента (0 - назад): ";
    int idx = ui::readInt(0, static_cast<int>(customers_.size()));
    if (idx == 0)
        return;
    activeCustomerIndex_ = idx - 1;
    runCustomerMenu();
}

// ===================== кабинет клиента =====================

void Menu::runCustomerMenu()
{
    int choice;
    do
    {
        Customer &c = customers_[activeCustomerIndex_];
        int unread = static_cast<int>(std::count_if(c.getNotifications().begin(), c.getNotifications().end(),
                                                    [](const Notification &n)
                                                    { return !n.isRead(); }));
        std::cout << "\n=== Кабинет клиента: " << c.getName() << " ===\n"
                  << "Баланс: " << ui::money(c.getBalance()) << " BYN | активных заказов: " << c.getActiveOrdersCount() << "\n"
                  << "1. Пополнить баланс\n"
                  << "2. Создать заказ\n"
                  << "3. Мои заказы\n"
                  << "4. Оплатить заказ\n"
                  << "5. Отменить заказ\n"
                  << "6. Запросить возврат\n"
                  << "7. Оставить отзыв\n"
                  << "8. Уведомления" << (unread > 0 ? " (новых: " + std::to_string(unread) + ")" : "") << "\n"
                  << "0. Выйти\n\nВыбор: ";
        choice = ui::readInt(0, 8);
        try
        {
            if (choice == 1)
            {
                std::cout << "Сумма пополнения, BYN: ";
                double amount = ui::readPositiveDouble();
                c.deposit(amount);
                logAction("Клиент " + c.getName() + " пополнил баланс на " + ui::money(amount) + " BYN");
                std::cout << "Баланс пополнен. Сейчас: " << ui::money(c.getBalance()) << " BYN\n";
            }
            else if (choice == 2)
                createOrder();
            else if (choice == 3)
                showMyOrders();
            else if (choice == 4)
                payOrderMenu();
            else if (choice == 5)
                cancelOrderMenu();
            else if (choice == 6)
                requestReturn();
            else if (choice == 7)
                leaveReview();
            else if (choice == 8)
                showMyNotifications();
        }
        catch (const std::exception &e)
        {
            std::cout << "ОШИБКА: " << e.what() << "\n";
        }
    } while (choice != 0);
    activeCustomerIndex_ = -1;
}

// ===================== заказы =====================

void Menu::createOrder()
{
    Customer &c = customers_[activeCustomerIndex_];
    std::vector<size_t> cart; // индексы книг в books_

    auto map = showBooks(true);
    while (true)
    {
        std::cout << "В корзине: " << cart.size() << " шт.\n"
                  << "Добавить книгу в корзину (№ в таблице, 0 - закончить выбор): ";
        int n = ui::readInt(0, static_cast<int>(map.size()));
        if (n == 0)
            break;
        size_t bi = map[n - 1];
        try
        {
            int already = static_cast<int>(std::count(cart.begin(), cart.end(), bi));
            if (books_[bi].getStockCount() - already <= 0)
                throw OutOfStockException("Книги \"" + books_[bi].getTitle() + "\" нет в наличии в нужном количестве");
            cart.push_back(bi);
            std::cout << "Добавлено: \"" << books_[bi].getTitle() << "\"\n";
        }
        catch (const OutOfStockException &e)
        {
            std::cout << "ОШИБКА: " << e.what() << "\n";
        }
    }

    if (cart.empty())
    {
        std::cout << "Корзина пуста, заказ не создан.\n";
        return;
    }

    Order order(nextOrderId_, c, today_);
    for (size_t bi : cart)
        order.addBook(books_[bi]);

    std::cout << "\nСостав заказа:\n";
    for (size_t bi : cart)
        std::cout << "  - " << books_[bi].getTitle() << " — " << ui::money(books_[bi].getPriceAmount()) << " BYN\n";
    std::cout << "Итого: " << ui::money(order.calculateTotal()) << " BYN\n"
              << "Оформить заказ? (1 - да, 0 - отмена): ";
    if (ui::readInt(0, 1) == 0)
    {
        std::cout << "Заказ отменён.\n";
        return;
    }

    for (size_t bi : cart)
        books_[bi].sellCopy(); // резервируем: из учёта списываем сразу, со склада — при отгрузке

    int id = nextOrderId_++;
    orders_.push_back({order, activeCustomerIndex_});
    c.addOrderId(id);
    c.incrementActiveOrders();
    metrics_.addOrder();
    metrics_.addBooks(static_cast<int>(cart.size()));

    Invoice invoice(nextInvoiceId_++, order);
    invoice.generate();
    c.addNotification(Notification("Создан заказ №" + std::to_string(id) + " на сумму " + ui::money(invoice.getAmount()) + " BYN"));
    logAction("Клиент " + c.getName() + " создал заказ №" + std::to_string(id));
    std::cout << "Заказ №" << id << " создан. Выставлен счёт на " << ui::money(invoice.getAmount()) << " BYN.\n"
              << "Оплатить сейчас с баланса? (1 - да, 0 - позже): ";
    if (ui::readInt(0, 1) == 1)
        payOrder(orders_.back());
}

void Menu::payOrder(OrderRecord &rec)
{
    Customer &c = customers_[rec.customerIdx];
    if (rec.order.getStatus() != "Created")
    {
        std::cout << "Заказ №" << rec.order.getId() << " уже не ждёт оплаты (" << ui::statusRu(rec.order.getStatus()) << ").\n";
        return;
    }
    double total = rec.order.calculateTotal();
    try
    {
        // Payment проверяет достаточность средств; реальное списание делаем у настоящего клиента
        Payment payment(nextPaymentId_++, c, Price(total, "BYN"));
        payment.processPayment();
        c.pay(total);
        rec.order.changeStatus("Paid");
        notifyCustomer(rec.customerIdx, "Заказ №" + std::to_string(rec.order.getId()) + " оплачен");
        logAction("Оплачен заказ №" + std::to_string(rec.order.getId()) + " (" + ui::money(total) + " BYN)");
        std::cout << "Заказ №" << rec.order.getId() << " оплачен. Остаток на балансе: " << ui::money(c.getBalance()) << " BYN\n";
    }
    catch (const InvalidPaymentException &e)
    {
        std::cout << "ОШИБКА ОПЛАТЫ: " << e.what() << " (нужно " << ui::money(total)
                  << " BYN, на балансе " << ui::money(c.getBalance()) << " BYN). Пополните баланс.\n";
    }
}

void Menu::payOrderMenu()
{
    std::vector<OrderRecord *> mine;
    for (auto &rec : orders_)
        if (rec.customerIdx == activeCustomerIndex_ && rec.order.getStatus() == "Created")
            mine.push_back(&rec);
    if (mine.empty())
    {
        std::cout << "Нет заказов, ожидающих оплаты.\n";
        return;
    }
    std::cout << "\nЗаказы к оплате:\n";
    for (size_t i = 0; i < mine.size(); ++i)
        std::cout << i + 1 << ". Заказ №" << mine[i]->order.getId() << " на " << ui::money(mine[i]->order.calculateTotal()) << " BYN\n";
    std::cout << "Выберите заказ (0 - назад): ";
    int n = ui::readInt(0, static_cast<int>(mine.size()));
    if (n != 0)
        payOrder(*mine[n - 1]);
}

void Menu::cancelOrderMenu()
{
    std::vector<OrderRecord *> mine;
    for (auto &rec : orders_)
        if (rec.customerIdx == activeCustomerIndex_ &&
            (rec.order.getStatus() == "Created" || rec.order.getStatus() == "Paid"))
            mine.push_back(&rec);
    if (mine.empty())
    {
        std::cout << "Нет заказов, которые ещё можно отменить (отменить можно до отгрузки).\n";
        return;
    }
    std::cout << "\nЗаказы, доступные для отмены:\n";
    for (size_t i = 0; i < mine.size(); ++i)
        std::cout << i + 1 << ". Заказ №" << mine[i]->order.getId() << " — " << ui::statusRu(mine[i]->order.getStatus()) << "\n";
    std::cout << "Выберите заказ (0 - назад): ";
    int n = ui::readInt(0, static_cast<int>(mine.size()));
    if (n == 0)
        return;

    OrderRecord &rec = *mine[n - 1];
    Customer &c = customers_[rec.customerIdx];
    bool wasPaid = rec.order.getStatus() == "Paid";
    for (const auto &title : rec.order.getBookTitles())
        if (Book *b = findBook(title))
            b->addStock(1); // возвращаем в учёт (физически книги и так лежат на складе)
    if (wasPaid)
        c.deposit(rec.order.calculateTotal());
    rec.order.changeStatus("Cancelled");
    c.decrementActiveOrders();
    notifyCustomer(rec.customerIdx, "Заказ №" + std::to_string(rec.order.getId()) + " отменён" + (wasPaid ? ", деньги возвращены на баланс" : ""));
    logAction("Клиент " + c.getName() + " отменил заказ №" + std::to_string(rec.order.getId()));
    std::cout << "Заказ №" << rec.order.getId() << " отменён" << (wasPaid ? ", " + ui::money(rec.order.calculateTotal()) + " BYN возвращено на баланс." : ".") << "\n";
}

void Menu::showMyOrders() const
{
    std::cout << "\nВаши заказы:\n";
    bool found = false;
    for (const auto &rec : orders_)
    {
        if (rec.customerIdx != activeCustomerIndex_)
            continue;
        found = true;
        std::cout << "Заказ №" << rec.order.getId() << " от " << rec.order.getDate().toString()
                  << " | " << ui::statusRu(rec.order.getStatus())
                  << " | " << ui::money(rec.order.calculateTotal()) << " BYN\n   Книги: ";
        auto titles = rec.order.getBookTitles();
        for (size_t i = 0; i < titles.size(); ++i)
            std::cout << (i ? "; " : "") << titles[i];
        std::cout << "\n";
    }
    if (!found)
        std::cout << "У вас пока нет заказов.\n";
}

// ===================== возврат, отзывы, уведомления =====================

void Menu::requestReturn()
{
    std::vector<OrderRecord *> mine;
    for (auto &rec : orders_)
    {
        if (rec.customerIdx != activeCustomerIndex_ || rec.order.getStatus() != "Delivered")
            continue;
        bool alreadyRequested = std::any_of(returns_.begin(), returns_.end(), [&](const ReturnRecord &r)
                                            { return r.orderId == rec.order.getId(); });
        if (!alreadyRequested)
            mine.push_back(&rec);
    }
    if (mine.empty())
    {
        std::cout << "Вернуть можно только доставленный заказ, по которому ещё нет запроса.\n";
        return;
    }
    std::cout << "\nДоставленные заказы:\n";
    for (size_t i = 0; i < mine.size(); ++i)
        std::cout << i + 1 << ". Заказ №" << mine[i]->order.getId() << " на " << ui::money(mine[i]->order.calculateTotal()) << " BYN\n";
    std::cout << "Выберите заказ (0 - назад): ";
    int n = ui::readInt(0, static_cast<int>(mine.size()));
    if (n == 0)
        return;

    std::string reason = ui::ask("Причина возврата: ");
    if (reason.empty())
        reason = "не указана";
    OrderRecord &rec = *mine[n - 1];
    returns_.push_back({rec.order.getId(), reason, ReturnRequest(rec.order, reason), false});
    logAction("Клиент " + customers_[rec.customerIdx].getName() + " запросил возврат по заказу №" + std::to_string(rec.order.getId()));
    std::cout << "Запрос на возврат отправлен менеджеру.\n";
}

void Menu::leaveReview()
{
    // Отзыв можно оставить только на книгу из доставленного заказа
    std::vector<std::string> titles;
    for (const auto &rec : orders_)
    {
        if (rec.customerIdx != activeCustomerIndex_ || rec.order.getStatus() != "Delivered")
            continue;
        for (const auto &t : rec.order.getBookTitles())
            if (!reviewed_.count({activeCustomerIndex_, t}) && std::find(titles.begin(), titles.end(), t) == titles.end())
                titles.push_back(t);
    }
    if (titles.empty())
    {
        std::cout << "Отзыв можно оставить на книгу из доставленного заказа (по одному отзыву на книгу).\n";
        return;
    }
    std::cout << "\nКниги, которые вы получили:\n";
    for (size_t i = 0; i < titles.size(); ++i)
        std::cout << i + 1 << ". " << titles[i] << "\n";
    std::cout << "Выберите книгу (0 - назад): ";
    int n = ui::readInt(0, static_cast<int>(titles.size()));
    if (n == 0)
        return;

    std::string text = ui::ask("Текст отзыва: ");
    if (text.empty())
    {
        std::cout << "Пустой отзыв не сохранён.\n";
        return;
    }
    std::cout << "Оценка (1-5): ";
    int score = ui::readInt(1, 5);
    Book *b = findBook(titles[n - 1]);
    b->addReview(Review(text, customers_[activeCustomerIndex_].getName()));
    b->addRating(score);
    reviewed_.insert({activeCustomerIndex_, titles[n - 1]});
    logAction("Клиент " + customers_[activeCustomerIndex_].getName() + " оставил отзыв на \"" + titles[n - 1] + "\"");
    std::cout << "Спасибо за отзыв!\n";
}

void Menu::showMyNotifications()
{
    Customer &c = customers_[activeCustomerIndex_];
    std::cout << "\nУведомления:\n";
    if (c.getNotifications().empty())
    {
        std::cout << "Нет уведомлений.\n";
        return;
    }
    for (auto &n : c.getNotifications())
    {
        std::cout << (n.isRead() ? "   " : "[новое] ") << n.getMessage() << "\n";
        n.markAsRead();
    }
}
