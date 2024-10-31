#include "CustomerManagement.h"
#include "SupplierRequest.h"
#include <fstream>
#include <algorithm>
#include <iostream>

void CustomerManagement::addCustomer(const Customer& customer) {
    customers.push_back(customer);
}

void CustomerManagement::displayCustomers() const {
    if (customers.empty()) {
        std::cout << "Немає зареєстрованих клієнтів." << std::endl;
        return;
    }
    for (const auto& customer : customers) {
        customer.display();
    }
}

bool CustomerManagement::editCustomer(int customerId) {
    // Залишаємо існуючий код editCustomer без змін
    for (auto& customer : customers) {
        if (customer.getCustomerId() == customerId) {
            string input;

            std::cout << "\nПоточні дані клієнта:\n";
            customer.display();

            // Змінити прізвище
            cout << "\nЗмінити прізвище клієнта? (y/n): ";
            getline(cin, input);
            if (input == "y") {
                cout << "Нове прізвище: ";
                getline(cin, input);
                if (!input.empty()) {
                    customer = Customer(input,
                                        customer.getFirstName(),
                                        customer.getPatronymic(),
                                        customer.getPhone(),
                                        customer.getCountry(),
                                        customer.getCity());
                    customer.setCustomerId(customerId);
                }
            }

            // Змінити ім'я
            cout << "Змінити ім'я клієнта? (y/n): ";
            getline(cin, input);
            if (input == "y") {
                cout << "Нове ім'я: ";
                getline(cin, input);
                if (!input.empty()) {
                    customer = Customer(customer.getLastName(),
                                        input,
                                        customer.getPatronymic(),
                                        customer.getPhone(),
                                        customer.getCountry(),
                                        customer.getCity());
                    customer.setCustomerId(customerId);
                }
            }

            // Змінити по батькові
            cout << "Змінити по батькові клієнта? (y/n): ";
            getline(cin, input);
            if (input == "y") {
                cout << "Нове по батькові: ";
                getline(cin, input);
                if (!input.empty()) {
                    customer = Customer(customer.getLastName(),
                                        customer.getFirstName(),
                                        input,
                                        customer.getPhone(),
                                        customer.getCountry(),
                                        customer.getCity());
                    customer.setCustomerId(customerId);
                }
            }

            // Змінити телефон
            cout << "Змінити номер телефону клієнта? (y/n): ";
            getline(cin, input);
            if (input == "y") {
                cout << "Новий номер телефону: ";
                getline(cin, input);
                if (!input.empty()) {
                    customer = Customer(customer.getLastName(),
                                        customer.getFirstName(),
                                        customer.getPatronymic(),
                                        input,
                                        customer.getCountry(),
                                        customer.getCity());
                    customer.setCustomerId(customerId);
                }
            }

            // Змінити країну
            cout << "Змінити країну клієнта? (y/n): ";
            getline(cin, input);
            if (input == "y") {
                cout << "Нова країна: ";
                getline(cin, input);
                if (!input.empty()) {
                    customer = Customer(customer.getLastName(),
                                        customer.getFirstName(),
                                        customer.getPatronymic(),
                                        customer.getPhone(),
                                        input,
                                        customer.getCity());
                    customer.setCustomerId(customerId);
                }
            }

            // Змінити місто
            cout << "Змінити місто клієнта? (y/n): ";
            getline(cin, input);
            if (input == "y") {
                cout << "Нове місто: ";
                getline(cin, input);
                if (!input.empty()) {
                    customer = Customer(customer.getLastName(),
                                        customer.getFirstName(),
                                        customer.getPatronymic(),
                                        customer.getPhone(),
                                        customer.getCountry(),
                                        input);
                    customer.setCustomerId(customerId);
                }
            }

            // Зберегти придбані автомобілі
            vector<int> previousPurchases = customer.getPurchasedCarIds();
            for (int carId : previousPurchases) {
                customer.addPurchasedCar(carId);
            }

            cout << "\nДані клієнта успішно оновлено!\n";
            return true;
        }
    }
    return false;
}

bool CustomerManagement::deleteCustomer(int customerId) {
    auto it = find_if(customers.begin(), customers.end(),
                      [customerId](const Customer& c) {
                          return c.getCustomerId() == customerId;
                      });
    if (it != customers.end()) {
        customers.erase(it);
        return true;
    }
    return false;
}

Customer* CustomerManagement::findCustomer(const string& lastName,
                                           const string& firstName,
                                           const string& patronymic,
                                           const string& phone) {
    for (auto& customer : customers) {
        if (customer.getLastName() == lastName &&
            customer.getFirstName() == firstName &&
            customer.getPatronymic() == patronymic &&
            customer.getPhone() == phone) {
            return &customer;
        }
    }
    return nullptr;
}

void CustomerManagement::loadCustomersFromFile(const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        Customer customer;
        customer.fromCSV(line);
        customers.push_back(customer);
    }
    file.close();
}

void CustomerManagement::saveCustomersToFile(const string& filename) const {
    ofstream file(filename);
    for (const auto& customer : customers) {
        file << customer.toCSV() << endl;
    }
    file.close();
}
