#include "OldDomesticCar.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

OldDomesticCar::OldDomesticCar() : id(0), sold(false), condition("Old") {}

OldDomesticCar::OldDomesticCar(int i, const std::string& b, int y, const std::string& s,
                               const std::string& c, double p, const std::string& cond)
        : id(i), brand(b), year(y), specifications(s), color(c),
          price(p), sold(false), condition(cond){
    if (year < 1900 || year > 2014) {
        throw std::invalid_argument("Old domestic car year must be between 1900 and 2014");
    }
}

// Getters implementation
int OldDomesticCar::getId() const { return id; }
std::string OldDomesticCar::getBrand() const { return brand; }
int OldDomesticCar::getYear() const { return year; }
std::string OldDomesticCar::getSpecifications() const { return specifications; }
std::string OldDomesticCar::getColor() const { return color; }
std::string OldDomesticCar::getCondition() const { return condition; }
double OldDomesticCar::getPrice() const { return price; }
bool OldDomesticCar::isSold() const { return sold; }

// Setters implementation
void OldDomesticCar::setId(int i) { id = i; }
void OldDomesticCar::setBrand(std::string b) { brand = b; }
void OldDomesticCar::setYear(int y) { year = y; }
void OldDomesticCar::setSpecifications(std::string s) { specifications = s; }
void OldDomesticCar::setColor(std::string c) { color = c; }
void OldDomesticCar::setPrice(double p) { price = p; }
void OldDomesticCar::setSold(bool s) { sold = s; }
void OldDomesticCar::setCondition(const std::string& newCondition) {
    condition = newCondition;
}

void OldDomesticCar::display() const {
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

std::string OldDomesticCar::toCSV() const {
    std::stringstream ss;
    ss << id << "," << brand << "," << year << "," << specifications << ","
       << color << "," << price << "," << condition << "," << (sold ? "1" : "0");
    return ss.str();
}

void OldDomesticCar::fromCSV(const std::string& data) {
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