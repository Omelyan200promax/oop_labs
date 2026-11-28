/**
 * @file Role.hpp
 * @brief Класс Role — роль пользователя.
 */
#pragma once
#include <string>

/**
 * @brief Роль: должность и уровень доступа.
 * @details Чем больше уровень, тем больше прав.
 */
class Role
{
private:
    std::string title_; /**< Название должности. */
    int accessLevel_; /**< Уровень доступа. */

public:
    /**
     * @brief Создаёт роль.
     * @param title Должность.
     * @param accessLevel Уровень доступа.
     */
    Role(std::string title, int accessLevel);
    /**
     * @brief Проверяет права.
     * @param requiredLevel Требуемый уровень.
     * @return true, если уровень роли не меньше требуемого.
     */
    bool hasAccess(int requiredLevel) const;
    /**
     * @brief Название должности.
     * @return Должность.
     */
    std::string getTitle() const;
    /**
     * @brief Уровень доступа.
     * @return Уровень.
     */
    int getAccessLevel() const;
};
