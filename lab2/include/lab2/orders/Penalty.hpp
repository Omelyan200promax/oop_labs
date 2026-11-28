/**
 * @file Penalty.hpp
 * @brief Класс Penalty — штраф.
 */
#pragma once
#include "lab2/common/Price.hpp"
#include <string>

/**
 * @brief Штраф сотруднику.
 */
class Penalty
{
private:
    std::string reason_; /**< Причина. */
    Price amount_; /**< Сумма штрафа. */

public:
    /**
     * @brief Создаёт штраф.
     * @param reason Причина.
     * @param amount Сумма.
     */
    Penalty(std::string reason, Price amount);
    /**
     * @brief Применяет штраф.
     * @details Заглушка: только печатает сообщение «Штраф применен: причина», зарплату не меняет.
     */
    void applyPenalty();
};
