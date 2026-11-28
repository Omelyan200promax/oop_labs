/**
 * @file Employee.hpp
 * @brief Класс Employee — сотрудник (базовый класс).
 */
#pragma once
#include <string>
#include "lab2/people/Role.hpp"

/**
 * @brief Сотрудник склада — базовый класс иерархии сотрудников.
 * @details Производные классы (Manager, Storekeeper, Courier, Auditor, Accountant, Editor) переопределяют виртуальный метод work().
 */
class Employee
{
protected:
    std::string name_; /**< ФИО. */
    int id_; /**< Табельный номер. */
    double salary_; /**< Зарплата, BYN. */
    Role role_; /**< Роль (должность и уровень доступа). */

public:
    /**
     * @brief Создаёт сотрудника.
     * @param name ФИО.
     * @param id Табельный номер.
     * @param salary Зарплата, BYN.
     * @param role Роль.
     */
    Employee(std::string name, int id, double salary, Role role);
    /**
     * @brief ФИО сотрудника.
     * @return Имя.
     */
    std::string getName() const;
    /**
     * @brief Зарплата.
     * @return Зарплата, BYN.
     */
    double getSalary() const;
    /**
     * @brief Роль сотрудника.
     * @return Роль.
     */
    Role getRole() const;
    /**
     * @brief Выполняет обычную работу сотрудника.
     * @details В базовом классе печатает «выполняет базовую работу»; наследники переопределяют (полиморфизм).
     */
    virtual void work();
};