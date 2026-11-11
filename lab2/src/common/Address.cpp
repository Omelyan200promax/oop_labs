#include "lab2/common/Address.hpp"

Address::Address(std::string city, std::string street) : city_(city), street_(street) {}
std::string Address::getFullAddress() const { return city_ + ", " + street_; }
