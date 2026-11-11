#include "lab2/common/ContactInfo.hpp"

ContactInfo::ContactInfo(std::string phone, std::string email) : phone_(phone), email_(email) {}
std::string ContactInfo::getEmail() const { return email_; }