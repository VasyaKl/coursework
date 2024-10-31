#include "NewCar.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

NewCar::NewCar() : id(0), sold(false), condition("New") {}

NewCar::NewCar(int i, const std::string& b, int y, const std::string& s,
               const std::string& c, double p, const std::string& cond)
        : id(i), brand(b), year(y), specifications(s), color(c),
          price(p), sold(false), condition(cond) {
    if (year < 2015 || year > 2024) {
        throw std::invalid_argument("New car year must be between 2015 and 2024");
    }
}

// Getters implementation
int NewCar::getId() const { return id; }
std::string NewCar::getBrand() const { return brand; }
int NewCar::getYear() const { return year; }
std::string NewCar::getSpecifications() const { return specifications; }
std::string NewCar::getColor() const { return color; }
double NewCar::getPrice() const { return price; }
bool NewCar::isSold() const { return sold; }
std::string NewCar::getCondition() const { return condition; }

// Setters implementation
void NewCar::setId(int i) { id = i; }
void NewCar::setBrand(std::string b) { brand = b; }
void NewCar::setYear(int y) { year = y; }
void NewCar::setSpecifications(std::string s) { specifications = s; }
void NewCar::setColor(std::string c) { color = c; }
void NewCar::setPrice(double p) { price = p; }
void NewCar::setSold(bool s) { sold = s; }
void NewCar::setCondition(const std::string& newCondition) {
    condition = newCondition;
}

void NewCar::display() const {
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

std::string NewCar::toCSV() const {
    std::stringstream ss;
    ss << id << "," << brand << "," << year << "," << specifications << ","
       << color << "," << price << "," << condition << "," << (sold ? "1" : "0");
    return ss.str();
}

void NewCar::fromCSV(const std::string& data) {
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

