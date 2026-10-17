#include "menu.hpp"
#include <windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Menu menu;
    menu.run();
    return 0;
}