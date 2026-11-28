/**
 * @file Accountant.hpp
 * @brief Класс Accountant — бухгалтер.
 */
#pragma once
#include "lab2/people/Employee.hpp"

/**
 * @brief Бухгалтер.
 * @details Наследуется от Employee, переопределяет work().
 */
class Accountant : public Employee
{
private:
    std::string taxId_; /**< УНП (налоговый номер). */

public:
    /**
     * @brief Создаёт бухгалтера.
     * @param name ФИО.
     * @param id Табельный номер.
     * @param salary Зарплата.
     * @param role Роль.
     * @param taxId Налоговый номер.
     */
    Accountant(std::string name, int id, double salary, Role role, std::string taxId);
    /**
     * @brief Работа бухгалтера: печатает сообщение о начислении зарплаты.
     */
    void work() override;
    /**
     * @brief Начисляет зарплату сотруднику.
     * @details Печатает сообщение с суммой зарплаты сотрудника; в данных ничего не меняет.
     * @param emp Сотрудник.
     */
    void calculateSalary(Employee &emp);
};
