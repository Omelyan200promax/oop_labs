#include "lab2/people/Editor.hpp"
#include <iostream>

Editor::Editor(std::string name, int id, double salary, int experienceYears)
    : Employee(name, id, salary), experienceYears_(experienceYears) {}

void Editor::editText()
{
    std::cout << getName() << " редактирует текст. Опыт: " << experienceYears_ << " лет\n";
}