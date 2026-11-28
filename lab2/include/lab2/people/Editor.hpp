/**
 * @file Editor.hpp
 * @brief Класс Editor — редактор.
 */
#pragma once
#include "lab2/people/Employee.hpp"

/**
 * @brief Редактор каталога.
 * @details Наследуется от Employee, переопределяет work().
 */
class Editor : public Employee
{
private:
    int experienceYears_; /**< Стаж, лет. */

public:
    /**
     * @brief Создаёт редактора.
     * @param name ФИО.
     * @param id Табельный номер.
     * @param salary Зарплата.
     * @param role Роль.
     * @param experienceYears Стаж, лет.
     */
    Editor(std::string name, int id, double salary, Role role, int experienceYears);
    /**
     * @brief Работа редактора: печатает сообщение о редактировании текста.
     */
    void work() override;
    /**
     * @brief Редактирует описание книги.
     * @details Заглушка: только печатает сообщение.
     */
    void editBook();
};
