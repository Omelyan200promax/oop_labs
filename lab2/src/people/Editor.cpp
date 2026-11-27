#include "lab2/people/Editor.hpp"
#include <iostream>

Editor::Editor(std::string name, int id, double salary, Role role, int experienceYears)
    : Employee(name, id, salary, role), experienceYears_(experienceYears) {}
void Editor::work() { std::cout << getName() << " редактирует текст.\n"; }
void Editor::editBook() { std::cout << getName() << " редактирует описание книги.\n"; }