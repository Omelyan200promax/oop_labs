#include "menu.hpp"  // заголовок с объявлением класса Menu
#include <iostream>  // std::cout, std::cin, std::getline
#include <limits>    // std::numeric_limits
#include <cctype>    // std::toupper
#include <stdexcept> // std::runtime_error
#include <memory>    // std::make_shared

// Конструктор по умолчанию. Ничего особенного делать не нужно —
// все поля уже инициализированы в menu.hpp.
Menu::Menu() = default;

// Читает целое число с консоли. Если ввод некорректный — повторяет.
int Menu::readInt(const std::string &prompt) const
{
    while (true)
    {                        // крутимся, пока не получим число
        std::cout << prompt; // печатаем подсказку
        int value;
        if (std::cin >> value)
        {                 // если ввод успешен
            clearInput(); // убираем остаток строки
            return value; // возвращаем число
        }
        std::cin.clear(); // сбрасываем флаг ошибки потока
        clearInput();     // убираем мусор из буфера
        std::cout << "Некорректный ввод, попробуйте снова.\n";
    }
}

// Читает строку целиком (до Enter). Нужно для ввода множеств вида "{a, b}".
std::string Menu::readLine(const std::string &prompt) const
{
    std::cout << prompt; // печатаем подсказку
    std::string line;
    std::getline(std::cin, line); // читаем строку до '\n'
    return line;
}

// «Сливает» всё оставшееся в буфере ввода до перевода строки.
// Нужно после std::cin >> value, чтобы следующий getline не прочитал пустоту.
void Menu::clearInput() const
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Точка входа меню. Просто запускает главный цикл.
void Menu::run()
{
    runMainLoop();
}

// Главный цикл: показываем меню, читаем выбор, обрабатываем.
void Menu::runMainLoop()
{
    while (true)
    { // бесконечный цикл — выход по '0'
        std::cout << "\n=== Главное меню ===\n";
        std::cout << "Текущий тип: "
                  << (mode_ == Mode::Sets ? "Множества" : "Мультимножества") << "\n";
        std::cout << "1. Работать с множествами\n";
        std::cout << "2. Работать с мультимножествами\n";
        std::cout << "0. Выход\n";

        int choice = readInt("Выбор: "); // читаем выбор пользователя

        if (choice == 1)
        { // пользователь выбрал множества
            switchMode(Mode::Sets);
            runTypeMenu();
        }
        else if (choice == 2)
        { // пользователь выбрал мультимножества
            switchMode(Mode::MultiSets);
            runTypeMenu();
        }
        else if (choice == 0)
        { // выход
            std::cout << "Пока!\n";
            break;
        }
        else
        { // неверный пункт — сообщаем
            std::cout << "Неверный пункт.\n";
        }
    }
}

// Возвращает ссылку на текущий список — множеств или мультимножеств.
// Ссылка, потому что дальше мы можем его менять.
std::vector<std::pair<char, std::shared_ptr<SetLike>>> &Menu::currentList()
{
    if (mode_ == Mode::Sets)
    {
        return sets_; // работаем с множествами
    }
    return multisets_; // иначе — с мультимножествами
}

// То же, но для константного объекта Menu — возвращать менять нельзя.
const std::vector<std::pair<char, std::shared_ptr<SetLike>>> &Menu::currentList() const
{
    if (mode_ == Mode::Sets)
    {
        return sets_;
    }
    return multisets_;
}

// Переключение режима Sets ↔ MultiSets.
void Menu::switchMode(Mode newMode)
{
    mode_ = newMode;
}

// Показывает список множеств или мультимножеств текущего типа.
void Menu::showCurrentList() const
{
    const auto &list = currentList(); // получаем ссылку на список
    if (list.empty())
    { // если пусто — сообщаем
        std::cout << "Список пуст.\n";
        return;
    }
    for (const auto &entry : list)
    {                                      // иначе печатаем каждую пару
        std::cout << entry.first << " = "; // имя, например "A = "
        entry.second->print(std::cout);    // сам объект через виртуальный print
        std::cout << "\n";
    }
}

// Просит пользователя выбрать одно множество из текущего списка.
// Возвращает shared_ptr на выбранное. Бросает исключение при ошибке.
std::shared_ptr<SetLike> Menu::selectFromList(const std::string &prompt) const
{
    const auto &list = currentList();
    if (list.empty())
    { // список пуст — выбирать нечего
        throw std::runtime_error("Список пуст");
    }
    showCurrentList(); // сначала показываем, из чего выбирать
    char name;
    std::cout << prompt;                          // например "Введите имя множества: "
    std::cin >> name;                             // читаем имя (одну букву)
    clearInput();                                 // убираем остаток строки
    name = static_cast<char>(std::toupper(name)); // к верхнему регистру

    for (const auto &entry : list)
    { // ищем в списке
        if (entry.first == name)
        {
            return entry.second; // нашли — возвращаем
        }
    }
    throw std::runtime_error("Множество с таким именем не найдено");
}

// Генерирует следующее свободное имя: A, B, ..., Z.
char Menu::nextName() const
{
    const auto &list = currentList();
    for (char c = 'A'; c <= 'Z'; ++c)
    {                      // идём по алфавиту
        bool used = false; // помечаем, занята ли буква
        for (const auto &entry : list)
        {
            if (entry.first == c)
            { // если имя уже есть в списке
                used = true;
                break;
            }
        }
        if (!used)
        { // нашли свободную букву
            return c;
        }
    }
    throw std::runtime_error("Свободных имён не осталось");
}

// Цикл меню внутри выбранного типа (Sets или MultiSets).
void Menu::runTypeMenu()
{
    while (true)
    {
        std::cout << "\n=== Меню ("
                  << (mode_ == Mode::Sets ? "Множества" : "Мультимножества")
                  << ") ===\n";
        std::cout << "1. Создать\n";
        std::cout << "2. Удалить\n";
        std::cout << "3. Показать все\n";
        std::cout << "4. Унарные операции\n";
        std::cout << "5. Бинарные операции\n";
        std::cout << "0. Назад\n";

        int choice = readInt("Выбор: ");

        if (choice == 1)
        {
            handleCreate();
        }
        else if (choice == 2)
        {
            handleRemove();
        }
        else if (choice == 3)
        {
            handleShowAll();
        }
        else if (choice == 4)
        {
            handleUnary();
        }
        else if (choice == 5)
        {
            handleBinary();
        }
        else if (choice == 0)
        {
            break; // возвращаемся в главное меню
        }
        else
        {
            std::cout << "Неверный пункт.\n";
        }
    }
}

// Создать новое множество (или мультимножество) из строки.
void Menu::handleCreate()
{
    std::string text = readLine("Введите множество в формате {a, b, {c}}: ");
    try
    {
        std::shared_ptr<SetLike> created;
        if (mode_ == Mode::Sets)
        {
            created = std::make_shared<Set>(Set::fromString(text));
        }
        else
        {
            created = std::make_shared<MultiSet>(MultiSet::fromString(text));
        }
        char name = nextName(); // A, B, C, ...
        currentList().push_back({name, created});
        std::cout << "Создано: " << name << " = ";
        created->print(std::cout);
        std::cout << "\n";
    }
    catch (const std::exception &e)
    {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}

// Удалить множество по имени.
void Menu::handleRemove()
{
    if (currentList().empty())
    {
        std::cout << "Список пуст.\n";
        return;
    }
    try
    {
        auto target = selectFromList("Введите имя для удаления: ");
        auto &list = currentList();
        for (auto it = list.begin(); it != list.end(); ++it)
        {
            if (it->second == target)
            {
                std::cout << "Удалено: " << it->first << "\n";
                list.erase(it);
                return;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}

// Показать все множества текущего типа.
void Menu::handleShowAll() const
{
    showCurrentList();
}

void Menu::handleUnary()
{
    if (currentList().empty())
    {
        std::cout << "Список пуст.\n";
        return;
    }

    try
    {
        auto target = selectFromList("Выберите множество: ");

        std::cout << "\n1. Проверить на пустоту\n";
        std::cout << "2. Мощность\n";
        std::cout << "3. Булеан\n";
        std::cout << "0. Назад\n";
        int choice = readInt("Выбор: ");

        if (choice == 1)
        {
            std::cout << (target->empty() ? "Пусто" : "Не пусто") << "\n";
        }
        else if (choice == 2)
        {
            std::cout << "Мощность: " << target->size() << "\n";
        }
        else if (choice == 3)
        {
            auto subsets = target->powerSet();
            std::cout << "Булеан (" << subsets.size() << " подмножеств):\n";
            for (const auto &subset : subsets)
            {
                std::cout << "  ";
                subset->print(std::cout);
                std::cout << "\n";
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}

void Menu::handleBinary()
{
    if (currentList().size() < 2)
    {
        std::cout << "Нужно хотя бы 2 множества в списке.\n";
        return;
    }

    try
    {
        auto first = selectFromList("Выберите первое множество: ");
        auto second = selectFromList("Выберите второе множество: ");

        std::cout << "\n1. Объединение (+)\n";
        std::cout << "2. Пересечение (*)\n";
        std::cout << "3. Разность (-)\n";
        std::cout << "0. Назад\n";
        int choice = readInt("Выбор: ");

        std::shared_ptr<SetLike> result;

        if (mode_ == Mode::Sets)
        {
            auto a = std::dynamic_pointer_cast<Set>(first);
            auto b = std::dynamic_pointer_cast<Set>(second);

            if (choice == 1)
            {
                result = std::make_shared<Set>(*a + *b);
            }
            else if (choice == 2)
            {
                result = std::make_shared<Set>(*a * *b);
            }
            else if (choice == 3)
            {
                result = std::make_shared<Set>(*a - *b);
            }
            else
            {
                return;
            }
        }
        else
        {
            auto a = std::dynamic_pointer_cast<MultiSet>(first);
            auto b = std::dynamic_pointer_cast<MultiSet>(second);

            if (choice == 1)
            {
                result = std::make_shared<MultiSet>(*a + *b);
            }
            else if (choice == 2)
            {
                result = std::make_shared<MultiSet>(*a * *b);
            }
            else if (choice == 3)
            {
                result = std::make_shared<MultiSet>(*a - *b);
            }
            else
            {
                return;
            }
        }

        std::cout << "Результат: ";
        result->print(std::cout);
        std::cout << "\n";

        int save = readInt("Сохранить результат? (1 — да, 0 — нет): ");
        if (save == 1)
        {
            char name = nextName();
            currentList().push_back({name, result});
            std::cout << "Сохранено как " << name << "\n";
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}