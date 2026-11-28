/**
 * @file Auditor.hpp
 * @brief Класс Auditor — аудитор.
 */
#pragma once
#include "lab2/people/Employee.hpp"

/**
 * @brief Аудитор склада.
 * @details Наследуется от Employee, переопределяет work().
 */
class Auditor : public Employee
{
public:
    /**
     * @brief Создаёт аудитора.
     * @param name ФИО.
     * @param id Табельный номер.
     * @param salary Зарплата.
     * @param role Роль.
     */
    Auditor(std::string name, int id, double salary, Role role);
    /**
     * @brief Работа аудитора: печатает сообщение о проведении аудита.
     */
    void work() override;
    /**
     * @brief Запускает инвентаризацию.
     * @details Заглушка: только печатает сообщение; саму сверку выполняет меню.
     */
    void checkInventory();
};