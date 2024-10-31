#ifndef COURSEWORKAVTO_SUPPLIERREQUESTMANAGEMENT_H
#define COURSEWORKAVTO_SUPPLIERREQUESTMANAGEMENT_H

#include <vector>
#include "SupplierRequest.h"
#include "Customer.h"

class SupplierRequestManagement {
private:
    std::vector<SupplierRequest> requests;
    int nextRequestId;
    std::string filename;

public:
    SupplierRequestManagement(const std::string& file = "supplier_requests.txt");

    void addRequest(const Customer& customer, const std::string& carBrand,
                    int carYear, const std::string& specifications,
                    const std::string& condition, double price);

    void displayAllRequests() const;
    void displayCustomerRequests(const Customer& customer) const;

    void loadRequestsFromFile();
    void saveRequestsToFile() const;
};

#endif //COURSEWORKAVTO_SUPPLIERREQUESTMANAGEMENT_H



