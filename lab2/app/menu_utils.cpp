#include "menu_utils.hpp"

#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace ui
{
    std::string trim(const std::string &str)
    {
        const char *ws = " \t\r\n";
        size_t b = str.find_first_not_of(ws);
        if (b == std::string::npos)
            return "";
        size_t e = str.find_last_not_of(ws);
        return str.substr(b, e - b + 1);
    }

    std::string readLine()
    {
        std::string line;
        if (!std::getline(std::cin, line))
        {
            std::cout << "\nВвод завершён. Выход из программы.\n";
            std::exit(0);
        }
        return trim(line);
    }

    std::string ask(const std::string &prompt)
    {
        std::cout << prompt;
        return readLine();
    }

    int readInt(int min, int max)
    {
        while (true)
        {
            std::string line = readLine();
            try
            {
                size_t pos = 0;
                int value = std::stoi(line, &pos);
                if (pos == line.size() && value >= min && value <= max)
                    return value;
            }
            catch (const std::exception &)
            {
            }
            std::cout << "Ошибка! Введите число от " << min << " до " << max << ": ";
        }
    }

    double readPositiveDouble()
    {
        while (true)
        {
            std::string line = readLine();
            for (char &ch : line)
                if (ch == ',')
                    ch = '.';
            try
            {
                size_t pos = 0;
                double value = std::stod(line, &pos);
                if (pos == line.size() && value > 0)
                    return value;
            }
            catch (const std::exception &)
            {
            }
            std::cout << "Ошибка! Введите положительное число: ";
        }
    }

    size_t utf8Length(const std::string &str)
    {
        size_t count = 0;
        for (unsigned char c : str)
            if ((c & 0xC0) != 0x80)
                ++count;
        return count;
    }

    std::string pad(const std::string &str, size_t width)
    {
        size_t len = utf8Length(str);
        if (len <= width)
            return str + std::string(width - len, ' ');

        // Обрезаем по символам, не разрывая многобайтовые последовательности
        std::string out;
        size_t chars = 0;
        for (size_t i = 0; i < str.size(); ++i)
        {
            unsigned char c = static_cast<unsigned char>(str[i]);
            if ((c & 0xC0) != 0x80)
            {
                if (chars == width - 1)
                    break;
                ++chars;
            }
            out += str[i];
        }
        return out + "…";
    }

    std::string lowerUtf8(const std::string &str)
    {
        std::string out;
        for (size_t i = 0; i < str.size(); ++i)
        {
            unsigned char c = static_cast<unsigned char>(str[i]);
            if (c < 0x80)
            {
                out += static_cast<char>(std::tolower(c));
            }
            else if (c == 0xD0 && i + 1 < str.size())
            {
                unsigned char d = static_cast<unsigned char>(str[++i]);
                if (d >= 0x90 && d <= 0x9F) // А-П -> а-п
                {
                    out += static_cast<char>(0xD0);
                    out += static_cast<char>(d + 0x20);
                }
                else if (d >= 0xA0 && d <= 0xAF) // Р-Я -> р-я
                {
                    out += static_cast<char>(0xD1);
                    out += static_cast<char>(d - 0x20);
                }
                else if (d == 0x81) // Ё -> ё
                {
                    out += static_cast<char>(0xD1);
                    out += static_cast<char>(0x91);
                }
                else
                {
                    out += static_cast<char>(c);
                    out += static_cast<char>(d);
                }
            }
            else
            {
                out += static_cast<char>(c);
            }
        }
        return out;
    }

    std::string money(double value)
    {
        std::ostringstream os;
        os << std::fixed << std::setprecision(2) << value;
        return os.str();
    }

    std::string statusRu(const std::string &status)
    {
        if (status == "Created")
            return "Создан (ждёт оплаты)";
        if (status == "Paid")
            return "Оплачен";
        if (status == "Shipped")
            return "Отгружен со склада";
        if (status == "In Delivery")
            return "В доставке";
        if (status == "Delivered")
            return "Доставлен";
        if (status == "Cancelled")
            return "Отменён";
        if (status == "Returned")
            return "Возвращён";
        return status;
    }

    CustomDate today()
    {
        std::time_t t = std::time(nullptr);
        std::tm *lt = std::localtime(&t);
        return CustomDate(lt->tm_mday, lt->tm_mon + 1, lt->tm_year + 1900);
    }
}
