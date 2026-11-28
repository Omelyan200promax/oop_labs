/**
 * @file Manager.hpp
 * @brief Класс Manager — менеджер.
 */
#pragma once
#include "lab2/people/Employee.hpp"

/**
 * @brief Менеджер отдела продаж.
 * @details Наследуется от Employee, переопределяет work().
 */
class Manager : public Employee
{
private:
    std::string department_; /**< Отдел. */

public:
    /**
     * @brief Создаёт менеджера.
     * @param name ФИО.
     * @param id Табельный номер.
     * @param salary Зарплата.
     * @param role Роль.
     * @param department Отдел.
     */
    Manager(std::string name, int id, double salary, Role role, std::string department);
    /**
     * @brief Работа менеджера: печатает сообщение об управлении отделом.
     */
    void work() override;
    /**
     * @brief Формирует отчёт по продажам.
     * @details Заглушка: только печатает сообщение; сам отчёт строит меню.
     */
    void createReport();
    /**
     * @brief Применяет скидку к книге.
     * @details Заглушка: только печатает сообщение; цену меняет Book::applyDiscount.
     */
    void applyDiscountToBook();
};
