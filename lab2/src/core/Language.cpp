#include "lab2/core/Language.hpp"

Language::Language(std::string name, std::string isoCode) : name_(name), isoCode_(isoCode) {}
std::string Language::getCode() const { return isoCode_; }
