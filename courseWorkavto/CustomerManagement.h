#ifndef COURSEWORKAVTO_CUSTOMERMANAGEMENT_H
#define COURSEWORKAVTO_CUSTOMERMANAGEMENT_H

#include "Customer.h"
#include <vector>
#include <string>

class CustomerManagement {
private:
    vector<Customer> customers;

public:
    void addCustomer(const Customer& customer);
    void displayCustomers() const;
    bool editCustomer(int customerId);
    bool deleteCustomer(int customerId);
    Customer* findCustomer(const string& lastName, const string& firstName,
                           const string& patronymic, const string& phone);
    void loadCustomersFromFile(const string& filename);
    void saveCustomersToFile(const string& filename) const;
};

#endif //COURSEWORKAVTO_CUSTOMERMANAGEMENT_H
