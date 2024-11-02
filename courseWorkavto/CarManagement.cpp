#include "CarManagement.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>


template<typename T>
bool CarManagement::carExists(const vector<T>& cars, int id) const {
    return std::any_of(cars.begin(), cars.end(),
                       [id](const T& car) { return car.getId() == id; });
}



void CarManagement::addNewCar(NewCar& car) {
    if (car.getYear() >= 2015 && car.getYear() <= 2024) {
        car.setId(nextNewId++);
        newCars.push_back(car);
        std::cout << "Новий автомобіль успішно додано." << std::endl;
    } else {
        std::cout << "Невірний рік для нової машини. Допустимий діапазон: 2015-2024." << std::endl;
    }
}

void CarManagement::addOldDomesticCar(OldDomesticCar& car) {
    if (car.getYear() >= 1900 && car.getYear() <= 2014) {
        car.setId(nextOldId++);
        oldDomesticCars.push_back(car);
        std::cout << "Старий вітчизняний автомобіль успішно додано." << std::endl;
    } else {
        std::cout << "Невірний рік для старого вітчизняного автомобіля. Допустимий діапазон: 1900-2014." << std::endl;
    }
}

void CarManagement::addForeignCar(ForeignCar& car) {
    // Перевіряємо чи марка не пуста
    if (car.getBrand().empty()) {
        std::cout << "Марка автомобіля не може бути пустою." << std::endl;
        return;
    }

    // Перевіряємо кожен символ в марці
    bool isValid = true;
    for (char c : car.getBrand()) {
        // Дозволяємо літери та дефіс
        if (!std::isalpha(c) && c != '-') {
            isValid = false;
            break;
        }
    }

    if (isValid) {
        car.setId(nextForeignId++);
        foreignCars.push_back(car);
        std::cout << "Іноземний автомобіль успішно додано." << std::endl;
    } else {
        std::cout << "Марка іноземного автомобіля повинна бути написана англійською мовою." << std::endl;
    }

}


void CarManagement::displayNewCars() const {
    if (newCars.empty()) {
        std::cout << "Немає доступних нових автомобілів." << std::endl;
        return;
    }
    for (const auto& car : newCars) {
        car.display();
    }
}

void CarManagement::displayOldDomesticCars() const {
    if (oldDomesticCars.empty()) {
        std::cout << "Немає доступних старих вітчизняних автомобілів." << std::endl;
        return;
    }
    for (const auto& car : oldDomesticCars) {
        car.display();
    }
}

void CarManagement::displayForeignCars() const {
    if (foreignCars.empty()) {
        std::cout << "Немає доступних іноземних автомобілів." << std::endl;
        return;
    }
    for (const auto& car : foreignCars) {
        car.display();
    }
}

void CarManagement::displayCars(bool onlyNew) const {
    if (onlyNew) {
        displayNewCars();
    } else {
        std::cout << "\nСписок усіх автомобілів:\n" << std::endl;
        displayNewCars();
        displayOldDomesticCars();
        displayForeignCars();
    }
}

void CarManagement::displayAvailableCars() const {
    std::cout << "\nДоступні автомобілі для покупки:\n" << std::endl;
    for (const auto& car : newCars) {
        if (!car.isSold()) {
            car.display();
        }
    }
    for (const auto& car : oldDomesticCars) {
        if (!car.isSold()) {
            car.display();
        }
    }
    for (const auto& car : foreignCars) {
        if (!car.isSold()) {
            car.display();
        }
    }
}

void CarManagement::sellCar(int id) {
    auto sellCarInVector = [id](auto& cars) -> bool {
        for (auto& car : cars) {
            if (car.getId() == id && !car.isSold()) {
                car.setSold(true);
                std::cout << "Автомобіль успішно продано!" << std::endl;
                return true;
            }
        }
        return false;
    };

    if (!sellCarInVector(newCars) &&
        !sellCarInVector(oldDomesticCars) &&
        !sellCarInVector(foreignCars)) {
        std::cout << "Автомобіль з вказаним ID не знайдено або вже продано." << std::endl;
    }
}

void CarManagement::saveCarsToFile(const char* filename) const {
    std::ofstream clearNew("newcars.txt", std::ofstream::trunc);
    std::ofstream clearOld("oldcars.txt", std::ofstream::trunc);
    std::ofstream clearForeign("foreigncars.txt", std::ofstream::trunc);
    clearNew.close();
    clearOld.close();
    clearForeign.close();

    // Зберігаємо нові автомобілі
    std::ofstream newCarsFile("newcars.txt");
    if (newCarsFile.is_open()) {
        for (const auto &car: newCars) {
            std::string specs = car.getSpecifications();
            std::replace(specs.begin(), specs.end(), '\n', ';');

            string carData = std::to_string(car.getId()) + "|" +
                             car.getBrand() + "|" +
                             std::to_string(car.getYear()) + "|" +
                             specs + "|" +
                             car.getColor() + "|" +
                             car.getCondition() + "|" +
                             std::to_string(car.getPrice()) + "|" +
                             (car.isSold() ? "1" : "0") + "\n";

            newCarsFile << carData;
        }
        newCarsFile.close();
    }

    // Зберігаємо старі вітчизняні автомобілі
    std::ofstream oldCarsFile("oldcars.txt");
    if (oldCarsFile.is_open()) {
        for (const auto &car: oldDomesticCars) {
            std::string specs = car.getSpecifications();
            std::replace(specs.begin(), specs.end(), '\n', ';');

            string carData = std::to_string(car.getId()) + "|" +
                             car.getBrand() + "|" +
                             std::to_string(car.getYear()) + "|" +
                             specs + "|" +
                             car.getColor() + "|" +
                             car.getCondition() + "|" +
                             std::to_string(car.getPrice()) + "|" +
                             (car.isSold() ? "1" : "0") + "\n";

            oldCarsFile << carData;
        }
        oldCarsFile.close();
    }

    // Зберігаємо іноземні автомобілі
    std::ofstream foreignCarsFile("foreigncars.txt");
    if (foreignCarsFile.is_open()) {
        for (const auto &car: foreignCars) {
            std::string specs = car.getSpecifications();
            std::replace(specs.begin(), specs.end(), '\n', ';');

            string carData = std::to_string(car.getId()) + "|" +
                             car.getBrand() + "|" +
                             std::to_string(car.getYear()) + "|" +
                             specs + "|" +
                             car.getColor() + "|" +
                             car.getCondition() + "|" +
                             std::to_string(car.getPrice()) + "|" +
                             (car.isSold() ? "1" : "0") + "\n";

            foreignCarsFile << carData;
        }
        foreignCarsFile.close();
    }
}

void CarManagement::loadCarsFromFile(const string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::vector<std::string> values;
        std::stringstream ss(line);
        std::string item;

        while (std::getline(ss, item, '|')) {
            values.push_back(item);
        }

        try {
            if (values.size() >= 8) {
                int id = std::stoi(values[0]);
                string brand = values[1];
                int year = std::stoi(values[2]);
                string specifications = values[3];
                std::replace(specifications.begin(), specifications.end(), ';', '\n');
                string color = values[4];
                string condition = values[5];
                double price = std::stod(values[6]);
                bool sold = (values[7] == "1");

                if (filename == "newcars.txt" && !carExists(newCars, id)) {
                    NewCar car(id, brand, year, specifications, color, price, condition);
                    car.setSold(sold);
                    newCars.push_back(car);
                    loadedCount++;
                    nextNewId = std::max(nextNewId, id + 1);
                }
                else if (filename == "oldcars.txt" && !carExists(oldDomesticCars, id)) {
                    OldDomesticCar car(id, brand, year, specifications, color, price, condition);
                    car.setSold(sold);
                    oldDomesticCars.push_back(car);
                    loadedCount++;
                    nextOldId = std::max(nextOldId, id + 1);
                }
                else if (filename == "foreigncars.txt" && !carExists(foreignCars, id)) {
                    ForeignCar car(id, brand, year, specifications, color, price, condition);
                    car.setSold(sold);
                    foreignCars.push_back(car);
                    loadedCount++;
                    nextForeignId = std::max(nextForeignId, id + 1);
                }
            }
        } catch (const std::exception& e) {
            continue;
        }
    }
    file.close();
}

// Delete methods implementation
bool CarManagement::deleteNewCar(int id) {
    auto it = std::find_if(newCars.begin(), newCars.end(),
                           [id](const NewCar& car) { return car.getId() == id; });
    if (it != newCars.end()) {
        newCars.erase(it);
        saveCarsToFile("newcars.txt");
        return true;
    }
    return false;
}

bool CarManagement::deleteOldDomesticCar(int id) {
    auto it = std::find_if(oldDomesticCars.begin(), oldDomesticCars.end(),
                           [id](const OldDomesticCar& car) { return car.getId() == id; });
    if (it != oldDomesticCars.end()) {
        oldDomesticCars.erase(it);
        saveCarsToFile("oldcars.txt");
        return true;
    }
    return false;
}

bool CarManagement::deleteForeignCar(int id) {
    auto it = std::find_if(foreignCars.begin(), foreignCars.end(),
                           [id](const ForeignCar& car) { return car.getId() == id; });
    if (it != foreignCars.end()) {
        foreignCars.erase(it);
        saveCarsToFile("foreigncars.txt");
        return true;
    }
    return false;
}

// Find methods implementation
NewCar* CarManagement::findNewCarById(int id) {
    auto it = std::find_if(newCars.begin(), newCars.end(),
                           [id](const NewCar& car) { return car.getId() == id; });
    if (it != newCars.end()) {
        return &(*it);
    }
    return nullptr;
}

OldDomesticCar* CarManagement::findOldDomesticCarById(int id) {
    auto it = std::find_if(oldDomesticCars.begin(), oldDomesticCars.end(),
                           [id](const OldDomesticCar& car) { return car.getId() == id; });
    if (it != oldDomesticCars.end()) {
        return &(*it);
    }
    return nullptr;
}

ForeignCar* CarManagement::findForeignCarById(int id) {
    auto it = std::find_if(foreignCars.begin(), foreignCars.end(),
                           [id](const ForeignCar& car) { return car.getId() == id; });
    if (it != foreignCars.end()) {
        return &(*it);
    }
    return nullptr;
}


void CarManagement::removeCar(const string& filename, int id) {
    if (filename == "new_cars.txt") {
        deleteNewCar(id);
    } else if (filename == "old_cars.txt") {
        deleteOldDomesticCar(id);
    } else if (filename == "foreign_cars.txt") {
        deleteForeignCar(id);
    }
}
template<typename T>
vector<T*> CarManagement::findMatchingCarsInVector(vector<T>& cars, const string& brand,
                                                   int yearFrom, int yearTo, const string& condition,
                                                   double minPrice, double maxPrice) {
    vector<T*> matchingCars;

    for(auto& car : cars) {
        if (!car.isSold() && // Check if not sold
            (brand.empty() || car.getBrand() == brand) && // If brand is empty, include all
            car.getYear() >= yearFrom &&
            car.getYear() <= yearTo &&
            (condition.empty() || car.getCondition() == condition) && // If condition is empty, include all
            car.getPrice() >= minPrice &&
            car.getPrice() <= maxPrice) {

            matchingCars.push_back(&car);
        }
    }

    return matchingCars;
}

vector<NewCar*> CarManagement::findMatchingCar(const string& brand, int yearFrom, int yearTo,
                                               const string& condition, double minPrice, double maxPrice) {
    return findMatchingCarsInVector(newCars, brand, yearFrom, yearTo, condition, minPrice, maxPrice);
}

vector<OldDomesticCar*> CarManagement::findMatchingOldCars(const string& brand, int yearFrom, int yearTo,
                                                           const string& condition, double minPrice, double maxPrice) {
    return findMatchingCarsInVector(oldDomesticCars, brand, yearFrom, yearTo, condition, minPrice, maxPrice);
}

vector<ForeignCar*> CarManagement::findMatchingForeignCars(const string& brand, int yearFrom, int yearTo,
                                                           const string& condition, double minPrice, double maxPrice) {
    return findMatchingCarsInVector(foreignCars, brand, yearFrom, yearTo, condition, minPrice, maxPrice);
}
