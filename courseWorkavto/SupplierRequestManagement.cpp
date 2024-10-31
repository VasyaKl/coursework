#include "SupplierRequestManagement.h"
#include <fstream>
#include <iostream>

SupplierRequestManagement::SupplierRequestManagement(const std::string& file)
        : nextRequestId(1), filename(file) {
    loadRequestsFromFile();
}

void SupplierRequestManagement::addRequest(const Customer& customer, const std::string& carBrand,
                                           int carYear, const std::string& specifications,
                                           const std::string& condition, double price) {
    SupplierRequest request(nextRequestId++,
                            customer.getName(),
                            customer.getPhone(),
                            carBrand,
                            carYear,
                            specifications,
                            condition,
                            price);

    requests.push_back(request);
    saveRequestsToFile();
}

void SupplierRequestManagement::displayAllRequests() const {
    if (requests.empty()) {
        std::cout << "Заяв від постачальників немає." << std::endl;
        return;
    }

    std::cout << "\nСписок всіх заяв:" << std::endl;
    for (const auto& request : requests) {
        request.display();
    }
}

void SupplierRequestManagement::displayCustomerRequests(const Customer& customer) const {
    bool found = false;
    std::cout << "\nВаші заяви:" << std::endl;

    for (const auto& request : requests) {
        if (request.getCustomerName() == customer.getName() &&
            request.getCustomerPhone() == customer.getPhone()) {
            request.display();
            found = true;
        }
    }

    if (!found) {
        std::cout << "У вас поки немає заяв." << std::endl;
    }
}

void SupplierRequestManagement::loadRequestsFromFile() {
    std::ifstream file(filename);
    if (!file) return;

    std::string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            SupplierRequest request;
            request.fromCSV(line);
            requests.push_back(request);
            if (request.getId() >= nextRequestId) {
                nextRequestId = request.getId() + 1;
            }
        }
    }
    file.close();
}

void SupplierRequestManagement::saveRequestsToFile() const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Помилка збереження заяв!" << std::endl;
        return;
    }

    for (const auto& request : requests) {
        file << request.toCSV() << std::endl;
    }
    file.close();
}