/**
 * @file CoverType.hpp
 * @brief Класс CoverType — тип обложки.
 */
#pragma once
#include <string>

/**
 * @brief Тип обложки книги (твёрдая или мягкая).
 */
class CoverType
{
private:
    std::string typeName_; /**< Название типа. */
    bool isHard_; /**< Признак твёрдой обложки. */

public:
    /**
     * @brief Создаёт тип обложки.
     * @param typeName Название.
     * @param isHard true — твёрдая обложка.
     */
    CoverType(std::string typeName, bool isHard);
    /**
     * @brief Проверяет твёрдость обложки.
     * @return true, если обложка твёрдая.
     */
    bool isHardCover() const;
};
