#pragma once
#include <vector>
#include <string>
class AuditLog
{
private:
    std::vector<std::string> records_;

public:
    void addRecord(std::string record);
    int getRecordCount() const;
};
