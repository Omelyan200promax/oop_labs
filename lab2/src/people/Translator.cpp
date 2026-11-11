#include "lab2/people/Translator.hpp"
#include <iostream>

Translator::Translator(std::string name, int id, double salary, std::string languagePair)
    : Employee(name, id, salary), languagePair_(languagePair) {}

void Translator::translate()
{
    std::cout << getName() << " переводит текст (" << languagePair_ << ")\n";
}
