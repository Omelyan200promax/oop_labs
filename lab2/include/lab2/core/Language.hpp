/**
 * @file Language.hpp
 * @brief Класс Language — язык издания.
 */
#pragma once
#include <string>

/**
 * @brief Язык издания книги.
 */
class Language
{
private:
    std::string name_; /**< Название языка. */
    std::string isoCode_; /**< Код языка по ISO. */

public:
    /**
     * @brief Создаёт язык.
     * @param name Название.
     * @param isoCode ISO-код.
     */
    Language(std::string name, std::string isoCode);
    /**
     * @brief Код языка.
     * @return ISO-код.
     */
    std::string getCode() const;
};
