#include "SupplierRequest.h"
#include <sstream>
#include <iomanip>
#include <ctime>
#include <iostream>
#include <algorithm>

SupplierRequest::SupplierRequest()
        : id(0), carYear(0), price(0.0), status("Новий"), isValid(true) {}

SupplierRequest::SupplierRequest(int id, const std::string& customerName, const std::string& customerPhone,
                                 const std::string& carBrand, int carYear, const std::string& specifications,
                                 const std::string& condition, double price)
        : id(id), customerName(customerName), customerPhone(customerPhone), carBrand(carBrand),
          carYear(carYear), specifications(specifications), condition(condition), price(price),
          status("Новий"), isValid(true) {

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
std::string SupplierRequest::getSpecifications() const { return specifications; }
std::string SupplierRequest::getCondition() const { return condition; }
double SupplierRequest::getPrice() const { return price; }
std::string SupplierRequest::getStatus() const { return status; }
std::string SupplierRequest::getRequestDate() const { return requestDate; }
bool SupplierRequest::getIsValid() const { return isValid; }

void SupplierRequest::display() const {
    if (!isValid) return;

    std::cout << "ID заявки: " << id << std::endl
              << "Дата створення: " << requestDate << std::endl
              << "Замовник: " << customerName << std::endl
              << "Телефон: " << customerPhone << std::endl
              << "Марка авто: " << carBrand << std::endl
              << "Рік випуску: " << carYear << std::endl
              << "Характеристики: " << specifications << std::endl
              << "Стан: " << condition << std::endl
              << "Ціна: " << price << std::endl
              << "Статус: " << status << std::endl
              << "-------------------" << std::endl;
}

std::string SupplierRequest::toCSV() const {
    if (!isValid) return "";

    // Замінюємо коми на крапки з комою для уникнення конфліктів при зчитуванні CSV
    std::string safeSpecs = specifications;
    std::replace(safeSpecs.begin(), safeSpecs.end(), ',', ';');

    std::stringstream ss;
    ss << id << ","
       << customerName << ","
       << customerPhone << ","
       << carBrand << ","
       << carYear << ","
       << safeSpecs << ","
       << condition << ","
       << std::fixed << std::setprecision(2) << price << ","
       << status << ","
       << requestDate;
    return ss.str();
}

bool SupplierRequest::fromCSV(const std::string& data) {
    std::stringstream ss(data);
    std::string item;

    try {
        // Читаємо ID
        if (!std::getline(ss, item, ',')) return false;
        id = std::stoi(item);

        // Читаємо інші поля
        std::getline(ss, customerName, ',');
        std::getline(ss, customerPhone, ',');
        std::getline(ss, carBrand, ',');

        if (!std::getline(ss, item, ',')) return false;
        carYear = std::stoi(item);

        std::getline(ss, specifications, ',');
        // Замінюємо крапки з комою назад на коми
        std::replace(specifications.begin(), specifications.end(), ';', ',');

        std::getline(ss, condition, ',');

        if (!std::getline(ss, item, ',')) return false;
        price = std::stod(item);

        std::getline(ss, status, ',');
        std::getline(ss, requestDate);

        isValid = true;
        return true;
    }
    catch (const std::exception&) {
        isValid = false;
        return false;
    }
}