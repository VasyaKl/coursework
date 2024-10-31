#include "AdminManagement.h"
#include <iostream>
#include <fstream>
#include <sstream>

AdminManagement::AdminManagement() {
    loadAdminsFromFile(ADMIN_FILE);
}

void AdminManagement::loadAdminsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return; // Файл не існує або не може бути відкритий
    }

    admins.clear(); // Очищаємо поточний вектор
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            Admin admin;
            admin.fromCSV(line);
            admins.push_back(admin);
        }
    }
    file.close();
}

void AdminManagement::saveAdminsFromFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Помилка: Неможливо відкрити файл для запису." << endl;
        return;
    }

    for (const auto& admin : admins) {
        file << admin.toCSV() << endl;
    }
    file.close();
}

bool AdminManagement::isFirstRun() {
    ifstream file(ADMIN_FILE);
    return !file.good() || file.peek() == ifstream::traits_type::eof();
}

bool AdminManagement::canRegisterAdmin() const {
    return admins.empty();
}

bool AdminManagement::registerAdmin(const string& username, const string& password) {
    if (!canRegisterAdmin()) {
        cout << "Адміністратор вже зареєстрований. Реєстрація нових адміністраторів заборонена." << endl;
        return false;
    }

    if (!isValidName(username)) {
        cout << "Ім'я повинно починатися з великої літери та не повинно мати інші символи окрім літер." << endl;
        return false;
    }

    if (!isValidPassword(password)) {
        cout << "Пароль повинен мати не менше 6 символів і повинен мати літери та цифри." << endl;
        return false;
    }

    Admin admin(username, password);
    admins.push_back(admin);
    saveAdminsFromFile(ADMIN_FILE);
    cout << "Адміністратор успішно зареєстрований!" << endl;
    return true;
}

bool AdminManagement::login(const string& username, const string& password) {
    for (const auto& admin : admins) {
        if (admin.getUsername() == username && admin.getPassword() == password) {
            return true;
        }
    }
    return false;
}

// Перевірка правильності імені
bool AdminManagement::isValidName(const string& name) {
    regex namePattern("^[A-Z][a-zA-Z]*$");
    return regex_match(name, namePattern);
}

// Перевірка правильності пароля
bool AdminManagement::isValidPassword(const string& password) {
    if (password.length() < 6) {
        return false;
    }
    regex passwordPattern("^[a-zA-Z0-9]+$");
    return regex_match(password, passwordPattern);
}
