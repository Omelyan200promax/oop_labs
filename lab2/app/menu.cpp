#include "menu.hpp"
#include "menu_utils.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>

#include "lab2/common/ContactInfo.hpp"
#include "lab2/common/Notification.hpp"
#include "lab2/exceptions/AccessDeniedException.hpp"
#include "lab2/exceptions/BookNotFoundException.hpp"
#include "lab2/people/Accountant.hpp"
#include "lab2/people/Auditor.hpp"
#include "lab2/people/Courier.hpp"
#include "lab2/people/Editor.hpp"
#include "lab2/people/Manager.hpp"
#include "lab2/people/Storekeeper.hpp"
#include "lab2/people/Supplier.hpp"

Menu::Menu()
    : warehouse_("Главный склад", Address("Минск", "ул. Складская, 1"), ContactInfo("+375170000000", "sklad@bsuir.by")),
      today_(ui::today()),
      nextOrderId_(1), nextInvoiceId_(1), nextPaymentId_(1), activeCustomerIndex_(-1)
{
    // ----- Каталог: 12 книг -----
    books_.push_back(Book("Война и мир", "978-5-04-118560-0", Author("Лев", "Толстой", "Россия", 1828, 1910), Publisher("Азбука", "СПб"), Genre("Роман-эпопея", "Исторический"), Category("Классика", "Русская литература"), Language("Русский", "ru"), CoverType("Твердая", true), Price(35.50, "BYN"), Dimensions(24.0, 17.0, 6.0), CustomDate(1, 1, 1869), 10));
    books_.push_back(Book("Преступление и наказание", "978-5-17-118290-7", Author("Фёдор", "Достоевский", "Россия", 1821, 1881), Publisher("АСТ", "Москва"), Genre("Психологический роман", "Драма"), Category("Классика", "Русская литература"), Language("Русский", "ru"), CoverType("Мягкая", false), Price(25.00, "BYN"), Dimensions(20.0, 13.0, 3.0), CustomDate(1, 1, 1866), 5));
    books_.push_back(Book("Анна Каренина", "978-5-04-099327-5", Author("Лев", "Толстой", "Россия", 1828, 1910), Publisher("Эксмо", "Москва"), Genre("Роман", "Трагедия"), Category("Классика", "Русская литература"), Language("Русский", "ru"), CoverType("Твердая", true), Price(42.00, "BYN"), Dimensions(22.0, 15.0, 5.0), CustomDate(1, 1, 1877), 8));
    books_.push_back(Book("Мастер и Маргарита", "978-5-17-087692-0", Author("Михаил", "Булгаков", "Россия", 1891, 1940), Publisher("АСТ", "Москва"), Genre("Мистика", "Сатира"), Category("Классика", "Русская литература"), Language("Русский", "ru"), CoverType("Твердая", true), Price(29.90, "BYN"), Dimensions(21.0, 14.0, 4.0), CustomDate(1, 1, 1967), 12));
    books_.push_back(Book("Отцы и дети", "978-5-04-116398-1", Author("Иван", "Тургенев", "Россия", 1818, 1883), Publisher("Азбука", "СПб"), Genre("Роман", "Реализм"), Category("Классика", "Русская литература"), Language("Русский", "ru"), CoverType("Мягкая", false), Price(21.50, "BYN"), Dimensions(19.0, 12.0, 2.0), CustomDate(1, 1, 1862), 7));
    books_.push_back(Book("Мёртвые души", "978-5-04-116400-1", Author("Николай", "Гоголь", "Россия", 1809, 1852), Publisher("Азбука", "СПб"), Genre("Поэма", "Сатира"), Category("Классика", "Русская литература"), Language("Русский", "ru"), CoverType("Твердая", true), Price(27.00, "BYN"), Dimensions(20.0, 13.0, 3.0), CustomDate(1, 1, 1842), 6));
    books_.push_back(Book("Герой нашего времени", "978-5-04-116305-9", Author("Михаил", "Лермонтов", "Россия", 1814, 1841), Publisher("Эксмо", "Москва"), Genre("Роман", "Психология"), Category("Классика", "Русская литература"), Language("Русский", "ru"), CoverType("Мягкая", false), Price(22.00, "BYN"), Dimensions(18.0, 11.0, 2.0), CustomDate(1, 1, 1840), 15));
    books_.push_back(Book("Тихий Дон", "978-5-17-118291-4", Author("Михаил", "Шолохов", "Россия", 1905, 1984), Publisher("АСТ", "Москва"), Genre("Роман-эпопея", "Драма"), Category("Классика", "Русская литература"), Language("Русский", "ru"), CoverType("Твердая", true), Price(48.00, "BYN"), Dimensions(25.0, 18.0, 7.0), CustomDate(1, 1, 1940), 4));
    books_.push_back(Book("Собачье сердце", "978-5-04-116402-5", Author("Михаил", "Булгаков", "Россия", 1891, 1940), Publisher("Азбука", "СПб"), Genre("Повесть", "Сатира"), Category("Классика", "Русская литература"), Language("Русский", "ru"), CoverType("Мягкая", false), Price(20.50, "BYN"), Dimensions(17.0, 11.0, 1.5), CustomDate(1, 1, 1925), 20));
    books_.push_back(Book("Евгений Онегин", "978-5-17-118292-1", Author("Александр", "Пушкин", "Россия", 1799, 1837), Publisher("Эксмо", "Москва"), Genre("Роман в стихах", "Классика"), Category("Классика", "Русская литература"), Language("Русский", "ru"), CoverType("Твердая", true), Price(26.00, "BYN"), Dimensions(19.0, 12.0, 2.5), CustomDate(1, 1, 1833), 10));
    books_.push_back(Book("Ревизор", "978-5-04-116403-2", Author("Николай", "Гоголь", "Россия", 1809, 1852), Publisher("Азбука", "СПб"), Genre("Комедия", "Сатира"), Category("Классика", "Русская литература"), Language("Русский", "ru"), CoverType("Мягкая", false), Price(20.00, "BYN"), Dimensions(18.0, 11.0, 1.0), CustomDate(1, 1, 1836), 8));
    books_.push_back(Book("Вишнёвый сад", "978-5-17-118293-8", Author("Антон", "Чехов", "Россия", 1860, 1904), Publisher("АСТ", "Москва"), Genre("Пьеса", "Драма"), Category("Классика", "Русская литература"), Language("Русский", "ru"), CoverType("Мягкая", false), Price(23.50, "BYN"), Dimensions(17.0, 11.0, 1.5), CustomDate(1, 1, 1904), 6));

    // ----- Клиенты -----
    customers_.push_back(Customer("Омелянчук Анна", ContactInfo("+375291234567", "anna@bsuir.by"), Address("Минск", "ул. Козлова, 15"), 350.0));
    customers_.push_back(Customer("Доронцова Дарья", ContactInfo("+375337654321", "daria@bsuir.by"), Address("Минск", "ул. Бобруйская, 10"), 500.0));
    customers_.push_back(Customer("Абрамова Арина", ContactInfo("+375441112233", "arina@bsuir.by"), Address("Минск", "пр-т Независимости, 65"), 250.0));
    customers_.push_back(Customer("Вакульчик Валерия", ContactInfo("+375255556677", "valeria@bsuir.by"), Address("Минск", "ул. Ленина, 5"), 150.0));
    customers_.push_back(Customer("Дубина Елизавета", ContactInfo("+375298889900", "liza@bsuir.by"), Address("Минск", "ул. Сурганова, 2"), 400.0));
    customers_.push_back(Customer("Куприянова Карина", ContactInfo("+375333334455", "karina@bsuir.by"), Address("Минск", "ул. Якуба Коласа, 12"), 200.0));

    // ----- Сотрудники (уровень доступа задаётся ролью) -----
    staff_.push_back(std::make_shared<Manager>("Шевченко Алексей", 1, 2500.0, Role("Менеджер", 5), "Отдел продаж"));
    staff_.push_back(std::make_shared<Storekeeper>("Явченко Никита", 2, 1800.0, Role("Кладовщик", 3), "Ночная"));
    staff_.push_back(std::make_shared<Courier>("Ясинский Платон", 3, 1500.0, Role("Курьер", 2), "Фургон"));
    staff_.push_back(std::make_shared<Auditor>("Кускова Вероника", 4, 2200.0, Role("Аудитор", 4)));
    staff_.push_back(std::make_shared<Accountant>("Данченко Ольга", 5, 2000.0, Role("Бухгалтер", 4), "123456789"));
    staff_.push_back(std::make_shared<Editor>("Лазарева Мария", 6, 1900.0, Role("Редактор", 3), 7));

    // ----- Оборудование склада -----
    equipment_.push_back(Equipment("Погрузчик", true));
    equipment_.push_back(Equipment("Сканер штрихкодов", false)); // сломан: нужно починить перед инвентаризацией
    equipment_.push_back(Equipment("Фургон", true));

    // ----- Поставщики и договоры -----
    deals_.push_back({"ООО \"Книжный мир\"", SupplyContract(Supplier("ООО \"Книжный мир\"", ContactInfo("+375172001122", "info@kmir.by")), CustomDate(1, 1, 2026), CustomDate(31, 12, 2027))});
    deals_.push_back({"ЗАО \"Литера\"", SupplyContract(Supplier("ЗАО \"Литера\"", ContactInfo("+375173334455", "sales@litera.by")), CustomDate(1, 1, 2024), CustomDate(31, 12, 2025))});

    // ----- Структура склада: 2 секции, в каждой стеллаж с полками -----
    Section classics("Классика", WarehouseZone("Сухая зона", 70));
    Rack rack1(1);
    rack1.addShelf(Shelf(1, 3));
    rack1.addShelf(Shelf(2, 3));
    classics.addRack(rack1);
    warehouse_.addSection(classics);

    Section reserve("Резерв", WarehouseZone("Зона B", 60));
    Rack rack2(2);
    rack2.addShelf(Shelf(3, 3));
    rack2.addShelf(Shelf(4, 3));
    reserve.addRack(rack2);
    warehouse_.addSection(reserve);

    fillWarehouse();
    logAction("Система запущена");
}

// ===================== служебное =====================

void Menu::fillWarehouse()
{
    // Физически раскладываем на склад столько экземпляров, сколько числится в базе
    for (const auto &b : books_)
        for (int i = 0; i < b.getStockCount(); ++i)
            warehouse_.storeBook(b.getWeight(), b.getTitle());
}

void Menu::logAction(const std::string &text)
{
    auditLog_.addRecord("[" + today_.toString() + "] " + text);
}

void Menu::notifyCustomer(int customerIdx, const std::string &text)
{
    customers_[customerIdx].addNotification(Notification(text));
}

void Menu::requireLevel(const SystemUser &user, int level, const std::string &what) const
{
    if (!user.loginAs(level))
        throw AccessDeniedException("Доступ запрещён: для действия \"" + what + "\" нужен уровень " + std::to_string(level) + " и выше");
}

Menu::OrderRecord *Menu::findOrder(int orderId)
{
    for (auto &rec : orders_)
        if (rec.order.getId() == orderId)
            return &rec;
    return nullptr;
}

Book *Menu::findBook(const std::string &title)
{
    for (auto &b : books_)
        if (b.getTitle() == title)
            return &b;
    return nullptr;
}

// Книги из оплаченных/созданных, но ещё не отгруженных заказов: в учёте их уже нет, физически ещё лежат на складе
int Menu::reservedCopies(const std::string &title) const
{
    int n = 0;
    for (const auto &rec : orders_)
    {
        const std::string st = rec.order.getStatus();
        if (st == "Created" || st == "Paid")
            for (const auto &t : rec.order.getBookTitles())
                if (t == title)
                    ++n;
    }
    return n;
}

Equipment *Menu::findEquipment(const std::string &name)
{
    for (auto &e : equipment_)
        if (e.getName() == name)
            return &e;
    return nullptr;
}

// Возвращает id заказов с указанным статусом
std::vector<int> Menu::listOrdersByStatus(const std::string &status)
{
    std::vector<int> ids;
    for (const auto &rec : orders_)
        if (rec.order.getStatus() == status)
            ids.push_back(rec.order.getId());
    return ids;
}

// ===================== главное меню =====================

void Menu::run()
{
    int choice;
    do
    {
        std::cout << "\n= Книжный склад: главное меню (" << today_.toString() << ") =\n";
        std::cout << "1. Каталог книг\n";
        std::cout << "2. Личный кабинет клиента\n";
        std::cout << "3. Кабинет сотрудника\n";
        std::cout << "4. Управление складом\n";
        std::cout << "0. Выход\n\nВыбор: ";
        choice = ui::readInt(0, 4);
        switch (choice)
        {
        case 1:
            runCatalogMenu();
            break;
        case 2:
            loginCustomer();
            break;
        case 3:
            loginEmployee();
            break;
        case 4:
            runWarehouseMenu();
            break;
        }
    } while (choice != 0);
    std::cout << "До свидания!\n";
}

// ===================== каталог =====================

void Menu::runCatalogMenu() const
{
    int c;
    do
    {
        std::cout << "\n- Каталог -\n"
                     "1. Все книги\n"
                     "2. Сортировать по наличию\n"
                     "3. Поиск по названию или автору\n"
                     "4. Найти по ISBN\n"
                     "5. Подробнее о книге\n"
                     "0. Назад\n\nВыбор: ";
        c = ui::readInt(0, 5);
        try
        {
            if (c == 1)
                showBooks(false);
            else if (c == 2)
                showBooks(true);
            else if (c == 3)
                searchBooks();
            else if (c == 4)
                findByIsbn();
            else if (c == 5)
                showBookDetails();
        }
        catch (const std::exception &e)
        {
            std::cout << "ОШИБКА: " << e.what() << "\n";
        }
    } while (c != 0);
}

// Печатает таблицу книг. Возвращает соответствие «номер в таблице -> индекс в books_»
// (при сортировке порядок в таблице отличается от порядка в каталоге).
std::vector<size_t> Menu::showBooks(bool sortByStock) const
{
    std::vector<size_t> order(books_.size());
    for (size_t i = 0; i < order.size(); ++i)
        order[i] = i;
    if (sortByStock)
    {
        std::stable_sort(order.begin(), order.end(), [this](size_t a, size_t b)
                         { return books_[a].getStockCount() > books_[b].getStockCount(); });
    }

    std::cout << "\nСписок книг" << (sortByStock ? " (по убыванию остатка)" : "") << ":\n";
    std::cout << ui::pad("№", 4) << ui::pad("Название", 28) << ui::pad("Автор", 22)
              << ui::pad("Жанр", 22) << ui::pad("Цена, BYN", 11) << ui::pad("Остаток", 9) << "Рейтинг\n";
    std::cout << std::string(104, '-') << "\n";

    for (size_t i = 0; i < order.size(); ++i)
    {
        const Book &b = books_[order[i]];
        std::cout << ui::pad(std::to_string(i + 1), 4)
                  << ui::pad(b.getTitle(), 28)
                  << ui::pad(b.getAuthorName(), 22)
                  << ui::pad(b.getGenreName(), 22)
                  << ui::pad(ui::money(b.getPriceAmount()), 11)
                  << ui::pad(b.getStockCount() > 0 ? std::to_string(b.getStockCount()) : "нет", 9);
        if (b.getRatingScore() > 0)
            std::cout << ui::money(b.getRatingScore()).substr(0, 3) << "/5";
        else
            std::cout << "—";
        std::cout << "\n";
    }
    return order;
}

void Menu::searchBooks() const
{
    std::string query = ui::lowerUtf8(ui::ask("Введите часть названия или автора: "));
    if (query.empty())
    {
        std::cout << "Пустой запрос.\n";
        return;
    }
    bool found = false;
    for (const auto &b : books_)
    {
        if (ui::lowerUtf8(b.getTitle()).find(query) != std::string::npos ||
            ui::lowerUtf8(b.getAuthorName()).find(query) != std::string::npos)
        {
            if (!found)
                std::cout << "Найдено:\n";
            std::cout << "  - " << b.getTitle() << " (" << b.getAuthorName() << "), "
                      << ui::money(b.getPriceAmount()) << " BYN, остаток: " << b.getStockCount() << "\n";
            found = true;
        }
    }
    if (!found)
        std::cout << "Ничего не найдено.\n";
}

void Menu::findByIsbn() const
{
    std::string isbn = ui::ask("Введите ISBN: ");
    for (const auto &b : books_)
    {
        if (b.getIsbn() == isbn)
        {
            std::cout << b.getInfo() << "\nЦена: " << ui::money(b.getPriceAmount()) << " BYN, остаток: " << b.getStockCount() << "\n";
            return;
        }
    }
    throw BookNotFoundException("Книга с ISBN \"" + isbn + "\" не найдена");
}

void Menu::showBookDetails() const
{
    auto map = showBooks(false);
    std::cout << "\nВыберите книгу (0 - отмена): ";
    int idx = ui::readInt(0, static_cast<int>(map.size()));
    if (idx == 0)
        return;
    const Book &b = books_[map[idx - 1]];
    std::cout << "\n" << b.getInfo()
              << "\nISBN: " << b.getIsbn()
              << "\nЦена: " << ui::money(b.getPriceAmount()) << " BYN"
              << "\nВ наличии: " << b.getStockCount() << " шт."
              << "\nРейтинг: " << (b.getRatingScore() > 0 ? ui::money(b.getRatingScore()).substr(0, 3) + "/5" : std::string("пока нет оценок"))
              << "\nОтзывы:\n";
    if (b.getReviews().empty())
        std::cout << "  Пока нет отзывов.\n";
    else
        for (const auto &r : b.getReviews())
            std::cout << "  [" << r.getAuthor() << "]: " << r.getText() << "\n";
}
