/**
 * @file SystemUser.hpp
 * @brief Класс SystemUser — пользователь системы.
 */
#pragma once
#include <string>
#include "lab2/people/Role.hpp"

/**
 * @brief Пользователь системы с логином и ролью; используется для проверки прав доступа.
 */
class SystemUser
{
private:
    std::string login_; /**< Логин. */
    Role role_; /**< Роль. */

public:
    /**
     * @brief Создаёт пользователя.
     * @param login Логин.
     * @param role Роль.
     */
    SystemUser(std::string login, Role role);
    /**
     * @brief Проверяет, достаточно ли прав для действия.
     * @param requiredLevel Требуемый уровень доступа.
     * @return true, если уровень роли не меньше требуемого.
     */
    bool loginAs(int requiredLevel) const;
};
