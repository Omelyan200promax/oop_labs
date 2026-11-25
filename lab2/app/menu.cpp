#include "menu.hpp"
#include "lab2/orders/Payment.hpp"
#include "lab2/orders/Delivery.hpp"
#include "lab2/orders/Shipment.hpp"
#include "lab2/orders/Invoice.hpp"
#include <iostream>
#include <limits>
#include <iomanip>

Menu::Menu() : nextOrderId_(1), warehouse_("Главный склад", Address("Минск", "ул. Складская, 1"), ContactInfo("+375170000000", "sklad@bsuir.by"))
{
    // 12 книг (Цены от 20 до 50 BYN, прописаны годы жизни авторов)
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

    // Клиенты (девочки из группы), балансы 100 - 500 BYN
    customers_.push_back(Customer("Омелянчук Анна", ContactInfo("+375291234567", "anna@bsuir.by"), Address("Минск", "ул. Козлова, 15"), 350.0));
    customers_.push_back(Customer("Доронцова Дарья", ContactInfo("+375337654321", "daria@bsuir.by"), Address("Минск", "ул. Бобруйская, 10"), 500.0));
    customers_.push_back(Customer("Абрамова Арина", ContactInfo("+375441112233", "arina@bsuir.by"), Address("Минск", "пр-т Независимости, 65"), 250.0));
    customers_.push_back(Customer("Вакульчик Валерия", ContactInfo("+375255556677", "valeria@bsuir.by"), Address("Минск", "ул. Ленина, 5"), 150.0));
    customers_.push_back(Customer("Дубина Елизавета", ContactInfo("+375298889900", "liza@bsuir.by"), Address("Минск", "ул. Сурганова, 2"), 400.0));
    customers_.push_back(Customer("Куприянова Карина", ContactInfo("+375333334455", "karina@bsuir.by"), Address("Минск", "ул. Якуба Коласа, 12"), 200.0));

    // Сотрудники
    staff_.push_back(std::make_shared<Manager>("Шевченко Алексей", 1, 2500.0, "Отдел продаж"));
    staff_.push_back(std::make_shared<Storekeeper>("Явченко Никита", 2, 1800.0, "Ночная"));
    staff_.push_back(std::make_shared<Courier>("Ясинский Платон", 3, 1500.0, "Фургон"));

    // Оборудование
    warehouse_.addEquipment(Equipment("Погрузчик", true));
    warehouse_.addEquipment(Equipment("Сканер штрих-кодов", false));
}

void Menu::showBooks() const
{
    std::cout << "\nСписок книг:\n";
    std::cout << std::left << std::setw(35) << "Название" << std::setw(30) << "Автор" << std::setw(15) << "Цена(BYN)" << std::setw(12) << "Остаток" << "Рейтинг\n";
    for (const auto &b : books_)
    {
        std::cout << std::left << std::setw(35) << b.getTitle() << std::setw(30) << b.getAuthorName() << std::setw(15) << b.getPriceAmount() << std::setw(12) << b.getStockCount() << b.getRatingScore() << "/5\n";
    }
}

void Menu::showBookDetails() const
{
    showBooks();
    std::cout << "Выберите книгу для просмотра отзывов (номер): ";
    int bookIndex;
    std::cin >> bookIndex;
    if (bookIndex < 1 || bookIndex > static_cast<int>(books_.size()))
        return;

    const Book &b = books_[bookIndex - 1];
    std::cout << "\nОтзывы о книге \"" << b.getTitle() << "\":\n";
    if (b.getReviews().empty())
    {
        std::cout << "Пока нет отзывов.\n";
    }
    else
    {
        for (const auto &rev : b.getReviews())
        {
            std::cout << "[" << rev.getAuthor() << "]: " << rev.getText() << "\n";
        }
    }
}

void Menu::showCustomers() const
{
    std::cout << "\nСписок клиентов:\n";
    std::cout << std::left << std::setw(30) << "Имя" << std::setw(30) << "Email" << std::setw(40) << "Адрес" << "Баланс (BYN)\n";
    for (const auto &c : customers_)
    {
        std::cout << std::left << std::setw(30) << c.getName() << std::setw(30) << c.getEmail() << std::setw(40) << c.getAddressStr() << c.getBalance() << "\n";
    }
}

void Menu::depositToCustomer()
{
    showCustomers();
    std::cout << "Выберите клиента для пополнения: ";
    int custIndex;
    std::cin >> custIndex;
    if (custIndex < 1 || custIndex > static_cast<int>(customers_.size()))
        return;

    std::cout << "Введите сумму (BYN): ";
    double amount;
    std::cin >> amount;
    customers_[custIndex - 1].deposit(amount);
    std::cout << "Баланс успешно пополнен!\n";
}

void Menu::searchBooks() const
{
    std::cout << "\nПоиск книг\n";
    std::cout << "1. По автору\n2. По названию\nВыбор: ";
    int choice;
    std::cin >> choice;

    std::string query;
    std::cout << "Введите запрос: ";
    std::cin >> query;

    bool found = false;
    for (const auto &b : books_)
    {
        bool match = false;
        if (choice == 1 && b.getAuthorName().find(query) != std::string::npos)
            match = true;
        if (choice == 2 && b.getTitle().find(query) != std::string::npos)
            match = true;

        if (match)
        {
            std::cout << "Найдено: " << b.getTitle() << " (" << b.getAuthorName() << ")\n";
            found = true;
        }
    }
    if (!found)
        std::cout << "Ничего не найдено.\n";
}

void Menu::showCustomerHistory() const
{
    showCustomers();
    std::cout << "Выберите клиента (номер): ";
    int custIndex;
    std::cin >> custIndex;
    if (custIndex < 1 || custIndex > static_cast<int>(customers_.size()))
        return;

    std::string targetName = customers_[custIndex - 1].getName();
    std::cout << "\nИстория заказов клиента " << targetName << ":\n";
    bool found = false;
    for (const auto &order : orders_)
    {
        if (order.getCustomer().getName() == targetName)
        {
            std::cout << "Заказ №" << " Статус: " << order.getStatus() << " Сумма: " << order.calculateTotal() << " BYN\n";
            found = true;
        }
    }
    if (!found)
        std::cout << "У клиента пока нет заказов.\n";
}

void Menu::showStaff() const
{
    std::cout << "\nСписок сотрудников:\n";
    for (const auto &emp : staff_)
    {
        emp->work();
    }
}

void Menu::showWarehouse() const
{
    std::cout << "\nИнформация о складе:\n";
    std::cout << "Название: Главный склад\n";
    std::cout << "Адрес: " << warehouse_.getAddress().getFullAddress() << "\n";
    std::cout << "Количество секций: " << warehouse_.getTotalSections() << "\n";
    std::cout << "Оборудование:\n";
    std::cout << " - Погрузчик: Работает\n";
    std::cout << " - Сканер: Требуется ремонт\n";
}

void Menu::createOrder()
{
    showCustomers();
    std::cout << "Выберите клиента (номер): ";
    int custIndex;
    std::cin >> custIndex;
    if (custIndex < 1 || custIndex > static_cast<int>(customers_.size()))
        return;

    Customer &customer = customers_[custIndex - 1];

    if (customer.getActiveOrdersCount() >= 2)
    {
        std::cout << "У клиента уже 2 активных заказа. Сначала оплатите или отмените их.\n";
        return;
    }

    showBooks();
    std::cout << "Выберите книгу (номер): ";
    int bookIndex;
    std::cin >> bookIndex;
    if (bookIndex < 1 || bookIndex > static_cast<int>(books_.size()))
        return;

    Book selectedBook = books_[bookIndex - 1];
    if (!selectedBook.isAvailable())
    {
        std::cout << "Этой книги нет в наличии!\n";
        return;
    }

    Order newOrder(nextOrderId_++, customer, CustomDate(25, 11, 2026));
    newOrder.addBook(selectedBook);
    orders_.push_back(newOrder);

    books_[bookIndex - 1].sellCopy();
    customer.incrementActiveOrders();

    Invoice inv(nextOrderId_, newOrder);
    inv.generate();
    std::cout << "Заказ создан. Сумма к оплате: " << inv.getAmount() << " BYN\n";
}

void Menu::cancelOrder()
{
    if (orders_.empty())
        return;
    std::cout << "\nСписок заказов:\n";
    for (size_t i = 0; i < orders_.size(); ++i)
    {
        std::cout << i + 1 << ". Статус: " << orders_[i].getStatus() << "\n";
    }
    std::cout << "Выберите заказ для отмены: ";
    int index;
    std::cin >> index;
    if (index < 1 || index > static_cast<int>(orders_.size()))
        return;

    Order &order = orders_[index - 1];
    if (order.getStatus() == "Delivered")
    {
        std::cout << "Доставленный заказ нельзя отменить!\n";
        return;
    }

    for (auto &c : customers_)
    {
        if (c.getName() == order.getCustomer().getName())
        {
            c.decrementActiveOrders();
            break;
        }
    }
    order.changeStatus("Cancelled");
    std::cout << "Заказ отменен. Книга возвращена на склад.\n";
}

void Menu::payOrder()
{
    if (orders_.empty())
        return;
    std::cout << "\nСписок заказов:\n";
    for (size_t i = 0; i < orders_.size(); ++i)
    {
        std::cout << i + 1 << ". Статус: " << orders_[i].getStatus() << ". Сумма: " << orders_[i].calculateTotal() << " BYN\n";
    }
    std::cout << "Выберите заказ для оплаты: ";
    int index;
    std::cin >> index;
    if (index < 1 || index > static_cast<int>(orders_.size()))
        return;

    Order &order = orders_[index - 1];
    if (order.getStatus() != "Created")
    {
        std::cout << "Заказ уже оплачен.\n";
        return;
    }

    Payment payment(1, order.getCustomer(), Price(order.calculateTotal(), "BYN"));
    try
    {
        payment.processPayment();
        order.changeStatus("Paid");
        std::cout << "Оплата прошла успешно!\n";
    }
    catch (const std::exception &e)
    {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}

void Menu::shipOrder()
{
    if (orders_.empty())
        return;
    std::cout << "\nСписок заказов:\n";
    for (size_t i = 0; i < orders_.size(); ++i)
    {
        std::cout << i + 1 << ". Статус: " << orders_[i].getStatus() << "\n";
    }
    std::cout << "Выберите заказ для отгрузки со склада: ";
    int index;
    std::cin >> index;
    if (index < 1 || index > static_cast<int>(orders_.size()))
        return;

    Order &order = orders_[index - 1];
    if (order.getStatus() != "Paid")
    {
        std::cout << "Сначала нужно оплатить!\n";
        return;
    }

    Shipment shipment(order, warehouse_);
    shipment.ship();
    std::cout << "Заказ отгружен со склада.\n";
}

void Menu::deliverOrder()
{
    if (orders_.empty())
        return;
    std::cout << "\nСписок заказов:\n";
    for (size_t i = 0; i < orders_.size(); ++i)
    {
        std::cout << i + 1 << ". Статус: " << orders_[i].getStatus() << "\n";
    }
    std::cout << "Выберите заказ для доставки: ";
    int index;
    std::cin >> index;
    if (index < 1 || index > static_cast<int>(orders_.size()))
        return;

    Order &order = orders_[index - 1];
    if (order.getStatus() != "Shipped")
    {
        std::cout << "Сначала отгрузите заказ!\n";
        return;
    }

    Delivery delivery(order, order.getCustomer().getAddress());
    delivery.startDelivery();
    delivery.completeDelivery();
    std::cout << "Заказ успешно доставлен.\n";
}

void Menu::leaveReview()
{
    showBooks();
    std::cout << "Выберите книгу (номер): ";
    int bookIndex;
    std::cin >> bookIndex;
    if (bookIndex < 1 || bookIndex > static_cast<int>(books_.size()))
        return;

    std::cout << "Введите текст отзыва: ";
    std::string text;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, text);

    std::cout << "Введите оценку (1-5): ";
    int score;
    std::cin >> score;

    books_[bookIndex - 1].addReview(Review(text, "Гость"));
    books_[bookIndex - 1].updateRating(score);
    std::cout << "Спасибо за отзыв!\n";
}

void Menu::run()
{
    int choice;
    do
    {
        std::cout << "\nМеню книжного склада БГУИР\n";
        std::cout << "1. Показать книги\n";
        std::cout << "2. Показать клиентов\n";
        std::cout << "3. Показать сотрудников\n";
        std::cout << "4. Информация о складе\n";
        std::cout << "5. Создать заказ\n";
        std::cout << "6. Оплатить заказ\n";
        std::cout << "7. Отгрузить заказ\n";
        std::cout << "8. Доставить заказ\n";
        std::cout << "9. Оставить отзыв\n";
        std::cout << "10. Посмотреть отзывы о книге\n";
        std::cout << "11. История заказов клиента\n";
        std::cout << "12. Пополнить баланс клиента\n";
        std::cout << "13. Поиск книг\n";
        std::cout << "14. Отменить заказ\n";
        std::cout << "0. Выход\n";
        std::cout << "Выбор: ";

        std::cin >> choice;
        switch (choice)
        {
        case 1:
            showBooks();
            break;
        case 2:
            showCustomers();
            break;
        case 3:
            showStaff();
            break;
        case 4:
            showWarehouse();
            break;
        case 5:
            createOrder();
            break;
        case 6:
            payOrder();
            break;
        case 7:
            shipOrder();
            break;
        case 8:
            deliverOrder();
            break;
        case 9:
            leaveReview();
            break;
        case 10:
            showBookDetails();
            break;
        case 11:
            showCustomerHistory();
            break;
        case 12:
            depositToCustomer();
            break;
        case 13:
            searchBooks();
            break;
        case 14:
            cancelOrder();
            break;
        case 0:
            std::cout << "Выход...\n";
            break;
        default:
            std::cout << "Неверный пункт.\n";
        }
    } while (choice != 0);
}