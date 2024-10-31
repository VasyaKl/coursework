#include "Customer.h"
#include <iostream>
#include <sstream>
#include <algorithm>

int Customer::nextId = 1;

Customer::Customer() : customerId(nextId++) {}

Customer::Customer(string ln, string fn, string p, string ph, string c, string ci)
        : customerId(nextId++), lastName(ln), firstName(fn), patronymic(p),
          phone(ph), country(c), city(ci) {}

int Customer::getCustomerId() const { return customerId; }
string Customer::getLastName() const { return lastName; }
string Customer::getFirstName() const { return firstName; }
string Customer::getPatronymic() const { return patronymic; }
string Customer::getPhone() const { return phone; }
string Customer::getCountry() const { return country; }
string Customer::getCity() const { return city; }
const vector<int>& Customer::getPurchasedCarIds() const { return purchasedCarIds; }

void Customer::setCustomerId(int id) {
    customerId = id;
}

void Customer::addPurchasedCar(int carId) {
    purchasedCarIds.push_back(carId);
}

string Customer::getName() const {
    return lastName + " " + firstName + " " + patronymic;
}

void Customer::display() const {
    cout << "ID: " << customerId
         << "\nПІБ: " << lastName << " " << firstName << " " << patronymic
         << "\nТелефон: " << phone
         << "\nКраїна: " << country
         << "\nМісто: " << city << endl;

    if (!purchasedCarIds.empty()) {
        cout << "Придбані автомобілі (ID): ";
        for (int id : purchasedCarIds) {
            cout << id << " ";
        }
        cout << endl;
    }
    cout << "-------------------" << endl;
}

string Customer::toCSV() const {
    stringstream ss;
    ss << customerId << "," << lastName << "," << firstName << ","
       << patronymic << "," << phone << "," << country << "," << city << ",";

    for (size_t i = 0; i < purchasedCarIds.size(); ++i) {
        if (i > 0) ss << ";";
        ss << purchasedCarIds[i];
    }
    return ss.str();
}

void Customer::fromCSV(const string& data) {
    stringstream ss(data);
    string carIds;
    string idStr;

    try {
        getline(ss, idStr, ',');
        if (!idStr.empty()) {
            customerId = stoi(idStr);
            nextId = max(nextId, customerId + 1);
        }

        getline(ss, lastName, ',');
        getline(ss, firstName, ',');
        getline(ss, patronymic, ',');
        getline(ss, phone, ',');
        getline(ss, country, ',');
        getline(ss, city, ',');
        getline(ss, carIds);

        purchasedCarIds.clear();
        stringstream carIdStream(carIds);
        string carId;
        while (getline(carIdStream, carId, ';')) {
            if (!carId.empty()) {
                try {
                    purchasedCarIds.push_back(stoi(carId));
                } catch (const std::invalid_argument&) {
                    // Skip invalid car IDs
                    continue;
                }
            }
        }
    } catch (const std::invalid_argument&) {
        // Handle invalid customer ID
        customerId = nextId++;
    }
}

void Customer::displayProfile() const {
    cout << "\nПрофіль клієнта:" << endl;
    cout << "----------------------------------------" << endl;
    cout << "ID клієнта: " << customerId << endl;
    cout << "Прізвище: " << lastName << endl;
    cout << "Ім'я: " << firstName << endl;
    cout << "По батькові: " << patronymic << endl;
    cout << "Телефон: " << phone << endl;
    cout << "Країна: " << country << endl;
    cout << "Місто: " << city << endl;

    if (!purchasedCarIds.empty()) {
        cout << "Придбані автомобілі (ID): ";
        for (int id : purchasedCarIds) {
            cout << id << " ";
        }
        cout << endl;
    }
    cout << "----------------------------------------" << endl;
}
