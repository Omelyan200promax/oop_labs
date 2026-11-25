#include "lab2/common/AuditLog.hpp"
void AuditLog::addRecord(std::string record) { records_.push_back(record); }
int AuditLog::getRecordCount() const { return records_.size(); }
