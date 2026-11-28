/**
 * @file AuditLog.hpp
 * @brief Класс AuditLog — журнал действий системы.
 */
#pragma once
#include <vector>
#include <string>
#include "lab2/common/LogEntry.hpp"

/**
 * @brief Журнал аудита: последовательность записей о действиях в системе.
 * @details Записи хранятся в порядке добавления и не удаляются.
 */
class AuditLog
{
private:
    std::vector<LogEntry> records_; /**< Записи журнала. */

public:
    /**
     * @brief Добавляет запись в конец журнала.
     * @param action Текст действия.
     */
    void addRecord(std::string action);
    /**
     * @brief Выводит журнал в стандартный вывод.
     * @details Каждая запись печатается строкой «- текст»; для пустого журнала выводится «Журнал пуст.».
     */
    void printLog() const;
};
