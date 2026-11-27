#include "menu.hpp"
#include "menu_utils.hpp"

#include <iostream>

#include "lab2/exceptions/InventoryMismatchException.hpp"
#include "lab2/exceptions/WarehouseException.hpp"
#include "lab2/warehouse/InventoryCheck.hpp"

void Menu::runWarehouseMenu()
{
    int choice;
    do
    {
        std::cout << "\n=== Управление складом ===\n"
                     "1. Структура склада\n"
                     "2. Инвентаризация\n"
                     "3. Оборудование\n"
                     "4. Метрики склада\n"
                     "0. Назад\n\nВыбор: ";
        choice = ui::readInt(0, 4);
        try
        {
            if (choice == 1)
                showWarehouseStructure();
            else if (choice == 2)
                runInventory();
            else if (choice == 3)
                manageEquipment();
            else if (choice == 4)
                showMetrics();
        }
        catch (const std::exception &e)
        {
            std::cout << "ОШИБКА: " << e.what() << "\n";
        }
    } while (choice != 0);
}

void Menu::showWarehouseStructure() const
{
    std::cout << "\n--- Структура склада ---\n";
    warehouse_.printFullStructure();
}

// Сверяет учёт (остаток в каталоге + зарезервированное под неотгруженные заказы) с тем, что реально лежит в коробках.
void Menu::runInventory()
{
    Equipment *scanner = findEquipment("Сканер штрихкодов");
    if (scanner && !scanner->checkStatus())
        throw WarehouseException("Сканер штрихкодов неисправен — инвентаризация невозможна. Почините его (Оборудование).");

    InventoryCheck check(today_);
    std::cout << "\nИнвентаризация от " << today_.toString() << "\n";
    std::cout << ui::pad("Книга", 28) << ui::pad("По учёту", 10) << ui::pad("На полках", 11) << "Результат\n";
    std::cout << std::string(60, '-') << "\n";

    std::string problems;
    for (const auto &b : books_)
    {
        int expected = b.getStockCount() + reservedCopies(b.getTitle());
        int actual = warehouse_.countBook(b.getTitle());
        std::cout << ui::pad(b.getTitle(), 28) << ui::pad(std::to_string(expected), 10) << ui::pad(std::to_string(actual), 11)
                  << (expected == actual ? "ОК" : "РАСХОЖДЕНИЕ") << "\n";
        if (expected != actual)
        {
            int diff = actual - expected;
            problems += (problems.empty() ? "" : "; ") + std::string("\"") + b.getTitle() + "\" " +
                        (diff < 0 ? "недостача " + std::to_string(-diff) : "излишек " + std::to_string(diff)) + " шт.";
        }
    }
    check.complete();
    logAction(problems.empty() ? "Инвентаризация: расхождений нет" : "Инвентаризация: " + problems);

    if (!problems.empty())
        throw InventoryMismatchException("Обнаружены расхождения: " + problems);
    std::cout << "Инвентаризация " << (check.isCompleted() ? "завершена" : "не завершена") << ": расхождений нет.\n";
}

void Menu::manageEquipment()
{
    int choice;
    do
    {
        std::cout << "\nОборудование:\n";
        for (size_t i = 0; i < equipment_.size(); ++i)
            std::cout << i + 1 << ". " << ui::pad(equipment_[i].getName(), 20)
                      << (equipment_[i].checkStatus() ? "работает" : "СЛОМАНО") << "\n";
        std::cout << "Выберите оборудование для ремонта (0 - назад): ";
        choice = ui::readInt(0, static_cast<int>(equipment_.size()));
        if (choice == 0)
            break;
        Equipment &e = equipment_[choice - 1];
        if (e.checkStatus())
        {
            std::cout << e.getName() << " и так исправно.\n";
            continue;
        }
        e.repair();
        logAction("Отремонтировано: " + e.getName());
        std::cout << e.getName() << " починено!\n";
    } while (true);
}

void Menu::showMetrics() const
{
    int reserved = 0, pending = 0;
    for (const auto &rec : orders_)
    {
        const std::string st = rec.order.getStatus();
        if (st == "Created" || st == "Paid")
            ++pending;
    }
    for (const auto &b : books_)
        reserved += reservedCopies(b.getTitle());

    std::cout << "\n--- Метрики склада ---\n"
              << "Всего заказов оформлено: " << orders_.size() << "\n"
              << "Среднее число книг в заказе: " << metrics_.getAverageBooksPerOrder() << "\n"
              << "Заказов ждут отгрузки/оплаты: " << pending << " (зарезервировано книг: " << reserved << ")\n"
              << "Книг физически на складе: " << warehouse_.getTotalStored() << "\n";
}
