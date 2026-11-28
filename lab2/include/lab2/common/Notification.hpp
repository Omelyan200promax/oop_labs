/**
 * @file Notification.hpp
 * @brief Класс Notification — уведомление пользователю.
 */
#pragma once
#include <string>
/**
 * @brief Уведомление клиенту с признаком прочтения.
 * @details После создания считается непрочитанным.
 */
class Notification
{
private:
    std::string message_; /**< Текст уведомления. */
    bool isRead_; /**< Признак прочтения. */

public:
    /**
     * @brief Создаёт непрочитанное уведомление.
     * @param message Текст.
     */
    Notification(std::string message);
    /**
     * @brief Помечает уведомление прочитанным.
     */
    void markAsRead();
    /**
     * @brief Возвращает текст.
     * @return Текст уведомления.
     */
    std::string getMessage() const;
    /**
     * @brief Проверяет, прочитано ли уведомление.
     * @return true, если прочитано.
     */
    bool isRead() const;
};
