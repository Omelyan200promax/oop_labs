/**
 * @file Storekeeper.hpp
 * @brief Класс Storekeeper — кладовщик.
 */
#pragma once
#include "lab2/people/Employee.hpp"

/**
 * @brief Кладовщик.
 * @details Наследуется от Employee, переопределяет work().
 */
class Storekeeper : public Employee
{
private:
    std::string shift_; /**< Смена. */

public:
    /**
     * @brief Создаёт кладовщика.
     * @param name ФИО.
     * @param id Табельный номер.
     * @param salary Зарплата.
     * @param role Роль.
     * @param shift Смена.
     */
    Storekeeper(std::string name, int id, double salary, Role role, std::string shift);
    /**
     * @brief Работа кладовщика: печатает сообщение о приёмке товара в смену.
     */
    void work() override;
    /**
     * @brief Раскладывает книги по коробкам и полкам.
     * @details Заглушка: только печатает сообщение; физическое размещение выполняет Warehouse::storeBook.
     */
    void sortBooks();
};
