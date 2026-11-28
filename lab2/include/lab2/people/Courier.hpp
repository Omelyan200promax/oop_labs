/**
 * @file Courier.hpp
 * @brief Класс Courier — курьер.
 */
#pragma once
#include "lab2/people/Employee.hpp"

/**
 * @brief Курьер.
 * @details Наследуется от Employee, переопределяет work().
 */
class Courier : public Employee
{
private:
    std::string vehicle_; /**< Транспорт курьера. */

public:
    /**
     * @brief Создаёт курьера.
     * @param name ФИО.
     * @param id Табельный номер.
     * @param salary Зарплата.
     * @param role Роль.
     * @param vehicle Транспорт.
     */
    Courier(std::string name, int id, double salary, Role role, std::string vehicle);
    /**
     * @brief Работа курьера: печатает сообщение о доставке заказов на его транспорте.
     */
    void work() override;
    /**
     * @brief Отправляется доставлять заказ.
     * @details Заглушка: только печатает сообщение.
     */
    void deliverOrder();
};
