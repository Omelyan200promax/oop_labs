/**
 * @file Customer.hpp
 * @brief Класс Customer — клиент.
 */
#pragma once
#include <string>
#include "lab2/common/ContactInfo.hpp"
#include "lab2/common/Address.hpp"
#include "lab2/common/Notification.hpp"
#include <vector>

/**
 * @brief Клиент магазина: контакты, адрес, баланс, уведомления и номера заказов.
 */
class Customer
{
private:
    std::string name_; /**< Имя. */
    ContactInfo contact_; /**< Контакты. */
    Address address_; /**< Адрес доставки. */
    double balance_; /**< Баланс счёта, BYN. */
    int activeOrdersCount_ = 0; /**< Число активных заказов. */
    std::vector<Notification> notifications_; /**< Уведомления клиента. */
    /**
     * @brief Номера заказов клиента (хранятся ID, а не сами заказы).
     */
    std::vector<int> orderIds_; // Храним ID заказов, а не сами заказы

public:
    /**
     * @brief Создаёт клиента.
     * @param name Имя.
     * @param contact Контакты.
     * @param address Адрес.
     * @param balance Начальный баланс, BYN.
     */
    Customer(std::string name, ContactInfo contact, Address address, double balance);
    /**
     * @brief Списывает сумму с баланса.
     * @param amount Сумма, BYN.
     * @return true, если средств хватило и сумма списана; иначе false (баланс не меняется).
     */
    bool pay(double amount);

    /**
     * @brief Увеличивает счётчик активных заказов.
     */
    void incrementActiveOrders();
    /**
     * @brief Уменьшает счётчик активных заказов.
     * @details Ниже нуля счётчик не опускается.
     */
    void decrementActiveOrders();
    /**
     * @brief Пополняет баланс.
     * @details Неположительные суммы игнорируются.
     * @param amount Сумма, BYN.
     */
    void deposit(double amount);

    /**
     * @brief Имя клиента.
     * @return Имя.
     */
    std::string getName() const;
    /**
     * @brief Электронная почта.
     * @return Email.
     */
    std::string getEmail() const;
    /**
     * @brief Адрес строкой.
     * @return Строка «город, улица».
     */
    std::string getAddressStr() const;
    /**
     * @brief Баланс.
     * @return Баланс, BYN.
     */
    double getBalance() const;
    /**
     * @brief Число активных заказов.
     * @return Количество.
     */
    int getActiveOrdersCount() const;
    /**
     * @brief Адрес клиента.
     * @return Объект адреса.
     */
    Address getAddress() const;

    /**
     * @brief Добавляет уведомление.
     * @param notif Уведомление.
     */
    void addNotification(const Notification &notif);
    /**
     * @brief Уведомления клиента.
     * @return Ссылка на список (можно менять, например помечать прочитанными).
     */
    std::vector<Notification> &getNotifications();
    /**
     * @brief Запоминает номер заказа клиента.
     * @param orderId Номер заказа.
     */
    void addOrderId(int orderId);
    /**
     * @brief Номера заказов клиента.
     * @return Список номеров.
     */
    std::vector<int> getOrderIds() const;
};
