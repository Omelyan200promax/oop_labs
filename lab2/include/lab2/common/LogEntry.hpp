/**
 * @file LogEntry.hpp
 * @brief Класс LogEntry — запись журнала.
 */
#pragma once
#include <string>
/**
 * @brief Одна запись журнала аудита.
 */
class LogEntry
{
private:
    std::string action_; /**< Описание действия. */

public:
    /**
     * @brief Создаёт запись.
     * @param action Описание действия.
     */
    LogEntry(std::string action);
    /**
     * @brief Возвращает описание действия.
     * @return Текст записи.
     */
    std::string getAction() const;
};
