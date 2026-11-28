/**
 * @file InventoryCheck.hpp
 * @brief Класс InventoryCheck — инвентаризация.
 */
#pragma once
#include "lab2/common/CustomDate.hpp"

/**
 * @brief Инвентаризация склада на определённую дату.
 * @details Хранит только дату и признак завершения; сверку остатков выполняет вызывающий код.
 */
class InventoryCheck
{
private:
    CustomDate date_; /**< Дата проверки. */
    bool isCompleted_; /**< Признак завершения. */

public:
    /**
     * @brief Создаёт незавершённую проверку.
     * @param date Дата проверки.
     */
    InventoryCheck(CustomDate date);
    /**
     * @brief Отмечает проверку завершённой.
     */
    void complete();
    /**
     * @brief Проверяет, завершена ли инвентаризация.
     * @return true, если завершена.
     */
    bool isCompleted() const;
};
