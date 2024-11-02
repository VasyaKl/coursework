#ifndef COURSEWORKAVTO_SUPPLIERREQUEST_H
#define COURSEWORKAVTO_SUPPLIERREQUEST_H

#include <string>
#include "Customer.h"

class SupplierRequest {
private:
    int id;
    std::string customerName;
    std::string customerPhone;
    std::string carBrand;
    int carYear;
    std::string color;          // Виділяємо колір в окреме поле
    std::string condition;
    double price;
    std::string status;
    std::string requestDate;
    bool isValid;

    void extractColor(const std::string& specs);  // Новий метод для отримання кольору

public:
    SupplierRequest();
    SupplierRequest(int id, const std::string& customerName, const std::string& customerPhone,
                    const std::string& carBrand, int carYear, const std::string& specifications,
                    const std::string& condition, double price);

    // Getters
    int getId() const;
    std::string getCustomerName() const;
    std::string getCustomerPhone() const;
    std::string getCarBrand() const;
    int getCarYear() const;
    std::string getColor() const;     // Новий геттер для кольору
    std::string getCondition() const;
    double getPrice() const;
    std::string getStatus() const;
    std::string getRequestDate() const;
    bool getIsValid() const;

    void display() const;
    std::string toCSV() const;
    bool fromCSV(const std::string& data);
};

#endif