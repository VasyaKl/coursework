#include <iostream>
#include <string>
#include <codecvt>
#include "MainMenu.h"

// Замість Windows.h використовуємо Linux-сумісний код
void setConsoleCP() {
    std::locale::global(std::locale("en_US.UTF-8"));
    std::cout.imbue(std::locale());
    std::cin.imbue(std::locale());
}

int main() {

#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#else
    setlocale(LC_ALL, "");
#endif

    MainMenu menu;
    menu.showMenu();

    return 0;
}


