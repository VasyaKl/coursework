#include "SupplierRequest.h"
#include <sstream>
#include <iomanip>
#include <ctime>
#include <iostream>
#include <algorithm>

void SupplierRequest::extractColor(const std::string& specs) {
    std::stringstream ss(specs);
    std::string line;

    while (std::getline(ss, line)) {
        if (line.find("Колір") != std::string::npos) {
            size_t colonPos = line.find(':');
            if (colonPos != std::string::npos) {
                color = line.substr(colonPos + 1);
                // Видаляємо зайві пробіли
                color.erase(0, color.find_first_not_of(" \t"));
                color.erase(color.find_last_not_of(" \t") + 1);
            }
            break;
        }
    }
}

SupplierRequest::SupplierRequest()
        : id(0), carYear(0), price(0.0), status("Новий"), isValid(true), color("Не вказано") {}

SupplierRequest::SupplierRequest(int id, const std::string& customerName, const std::string& customerPhone,
                                 const std::string& carBrand, int carYear, const std::string& specifications,
                                 const std::string& condition, double price)
        : id(id), customerName(customerName), customerPhone(customerPhone), carBrand(carBrand),
          carYear(carYear), condition(condition), price(price),
          status("Новий"), isValid(true), color("Чорний") {

    extractColor(specifications);  // Витягуємо колір з технічних характеристик

    time_t now = time(nullptr);
    auto tm = *localtime(&now);
    std::stringstream ss;
    ss << std::put_time(&tm, "%d-%m-%Y");
    requestDate = ss.str();
}

// Getters implementation
int SupplierRequest::getId() const { return id; }
std::string SupplierRequest::getCustomerName() const { return customerName; }
std::string SupplierRequest::getCustomerPhone() const { return customerPhone; }
std::string SupplierRequest::getCarBrand() const { return carBrand; }
int SupplierRequest::getCarYear() const { return carYear; }
std::string SupplierRequest::getCondition() const { return condition; }
double SupplierRequest::getPrice() const { return price; }
std::string SupplierRequest::getStatus() const { return status; }
std::string SupplierRequest::getRequestDate() const { return requestDate; }
bool SupplierRequest::getIsValid() const { return isValid; }
std::string SupplierRequest::getColor() const { return color; }

void SupplierRequest::display() const {
    if (!isValid) return;

    std::cout << "ID заявки: " << id << std::endl
              << "Дата створення: " << requestDate << std::endl
              << "Замовник: " << customerName << std::endl
              << "Телефон: " << customerPhone << std::endl
              << "Марка авто: " << carBrand << std::endl
              << "Рік випуску: " << carYear << std::endl
              << "Колір: " << color << std::endl        // Додаємо виведення кольору
              << "Стан: " << condition << std::endl
              << "Ціна: " << std::fixed << std::setprecision(2) << price << " $ " << std::endl
              << "Статус: " << status << std::endl
              << "-------------------" << std::endl;
}

std::string SupplierRequest::toCSV() const {
    if (!isValid) return "";

    std::stringstream ss;
    ss << id << "|"
       << customerName << "|"
       << customerPhone << "|"
       << carBrand << "|"
       << carYear << "|"
       << color << "|"          // Зберігаємо колір замість всіх характеристик
       << condition << "|"
       << std::fixed << std::setprecision(2) << price << "|"
       << status << "|"
       << requestDate;
    return ss.str();
}

bool SupplierRequest::fromCSV(const std::string& data) {
    std::stringstream ss(data);
    std::string item;
    std::vector<std::string> values;

    try {
        while (std::getline(ss, item, '|')) {
            values.push_back(item);
        }

        if (values.size() < 10) return false;

        id = std::stoi(values[0]);
        customerName = values[1];
        customerPhone = values[2];
        carBrand = values[3];
        carYear = std::stoi(values[4]);
        color = values[5];          // Зчитуємо колір
        condition = values[6];
        price = std::stod(values[7]);
        status = values[8];
        requestDate = values[9];

        isValid = true;
        return true;
    }
    catch (const std::exception&) {
        isValid = false;
        return false;
    }
}