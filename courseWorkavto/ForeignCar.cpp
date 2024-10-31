#include "ForeignCar.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <regex>

ForeignCar::ForeignCar() : id(0), sold(false) {}

ForeignCar::ForeignCar(int i, const std::string& b, int y, const std::string& s,
                       const std::string& c, double p, const std::string& cond)
        : id(i), brand(b), year(y), specifications(s), color(c),
          price(p), sold(false), condition(cond) {
    if (!isEnglishBrand(b)) {
        throw std::invalid_argument("Foreign car brand must be in English");
    }
}

// Getters implementation
int ForeignCar::getId() const { return id; }
std::string ForeignCar::getBrand() const { return brand; }
int ForeignCar::getYear() const { return year; }
std::string ForeignCar::getSpecifications() const { return specifications; }
std::string ForeignCar::getColor() const { return color; }
std::string ForeignCar::getCondition() const { return condition; }
double ForeignCar::getPrice() const { return price; }
bool ForeignCar::isSold() const { return sold; }

// Setters implementation
void ForeignCar::setId(int i) { id = i; }
void ForeignCar::setBrand(std::string b) {
    if (!isEnglishBrand(b)) {
        throw std::invalid_argument("Foreign car brand must be in English");
    }
    brand = b;
}
void ForeignCar::setYear(int y) { year = y; }
void ForeignCar::setSpecifications(std::string s) { specifications = s; }
void ForeignCar::setColor(std::string c) { color = c; }
void ForeignCar::setPrice(double p) { price = p; }
void ForeignCar::setSold(bool s) { sold = s; }
void ForeignCar::setCondition(const std::string& newCondition) {
    condition = newCondition;
}

void ForeignCar::display() const {
    std::cout << "ID: " << id
              << "\nМарка: " << brand
              << "\nРік: " << year
              << "\nТехнічні характеристики: " << specifications
              << "\nКолір: " << color
              << "\nЦіна: " << price
              << "\nСтан: " << condition
              << "\nСтатус: " << (sold ? "Продано" : "В наявності")
              << "\n-------------------" << std::endl;
}

std::string ForeignCar::toCSV() const {
    std::stringstream ss;
    ss << id << "," << brand << "," << year << "," << specifications << ","
       << color << "," << price << "," << condition << "," << (sold ? "1" : "0");
    return ss.str();
}

void ForeignCar::fromCSV(const std::string& data) {
    std::stringstream ss(data);
    std::string soldStr;
    std::string item;

    getline(ss, item, ','); id = std::stoi(item);
    getline(ss, brand, ',');
    getline(ss, item, ','); year = std::stoi(item);
    getline(ss, specifications, ',');
    getline(ss, color, ',');
    getline(ss, item, ','); price = std::stod(item);
    getline(ss, condition, ',');
    getline(ss, soldStr);
    sold = (soldStr == "1");
}

bool ForeignCar::isEnglishBrand(const std::string& brand) {
    std::regex englishPattern("^[a-zA-Z0-9\\s-]+$");
    return std::regex_match(brand, englishPattern);
}