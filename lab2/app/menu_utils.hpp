#pragma once

#include <string>
#include "lab2/common/CustomDate.hpp"

// Вспомогательные функции консольного ввода/вывода для меню.
namespace ui
{
    // Читает строку; при конце ввода (Ctrl+D / Ctrl+Z) корректно завершает программу.
    std::string readLine();
    // Выводит приглашение и читает непустую по смыслу строку (пробелы по краям обрезаются).
    std::string ask(const std::string &prompt);
    // Читает целое число в диапазоне [min, max], пока ввод не станет корректным.
    int readInt(int min, int max);
    // Читает положительное вещественное число (принимает и запятую, и точку).
    double readPositiveDouble();

    // Длина строки в символах (а не в байтах) для UTF-8.
    size_t utf8Length(const std::string &str);
    // Дополняет пробелами / обрезает строку до width символов (с учётом кириллицы).
    std::string pad(const std::string &str, size_t width);
    // Приведение к нижнему регистру для латиницы и кириллицы (UTF-8).
    std::string lowerUtf8(const std::string &str);
    // Число с двумя знаками после запятой.
    std::string money(double value);
    // Перевод статуса заказа в читаемый вид.
    std::string statusRu(const std::string &status);
    // Сегодняшняя дата.
    CustomDate today();
    // Разбивает строку на слова по пробелам.
    std::string trim(const std::string &str);
}
