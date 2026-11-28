/**
 * @file SupplyContract.hpp
 * @brief Класс SupplyContract — договор поставки.
 */
#pragma once
#include "lab2/people/Supplier.hpp"
#include "lab2/common/CustomDate.hpp"

/**
 * @brief Договор поставки книг с поставщиком на определённый срок.
 */
class SupplyContract
{
private:
    Supplier supplier_; /**< Поставщик. */
    CustomDate startDate_; /**< Дата начала действия. */
    CustomDate endDate_; /**< Дата окончания действия. */

public:
    /**
     * @brief Создаёт договор.
     * @param supplier Поставщик.
     * @param start Дата начала.
     * @param end Дата окончания.
     */
    SupplyContract(Supplier supplier, CustomDate start, CustomDate end);
    /**
     * @brief Проверяет, действует ли договор на дату.
     * @param currentDate Проверяемая дата.
     * @return true, если дата лежит в промежутке [начало, окончание].
     */
    bool isActive(CustomDate currentDate) const;
    /**
     * @brief Поставщик по договору.
     * @return Ссылка на поставщика.
     */
    Supplier &getSupplier();
    /**
     * @brief Дата окончания договора.
     * @return Дата окончания.
     */
    CustomDate getEndDate() const;
};
