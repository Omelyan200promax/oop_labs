#include <gtest/gtest.h>
#include <string>
#include "lab2/common/AuditLog.hpp"

// Пустой журнал печатает сообщение о пустоте
TEST(AuditLog, EmptyLogPrintsMessage)
{
    AuditLog log;
    testing::internal::CaptureStdout();
    log.printLog();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("Журнал пуст"), std::string::npos);
}

// Записи печатаются в порядке добавления
TEST(AuditLog, PrintsRecordsInOrder)
{
    AuditLog log;
    log.addRecord("первое");
    log.addRecord("второе");
    testing::internal::CaptureStdout();
    log.printLog();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_EQ(out, "- первое\n- второе\n");
}

// После добавления записи сообщение о пустоте исчезает
TEST(AuditLog, NotEmptyAfterAdd)
{
    AuditLog log;
    log.addRecord("действие");
    testing::internal::CaptureStdout();
    log.printLog();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_EQ(out.find("Журнал пуст"), std::string::npos);
}
