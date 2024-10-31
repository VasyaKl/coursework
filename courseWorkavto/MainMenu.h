#ifndef COURSEWORKAVTO_MAINMENU_H
#define COURSEWORKAVTO_MAINMENU_H

#include <iostream>
#include <limits>
#include <string>
#include "NewCar.h"
#include "ForeignCar.h"
#include "CarManagement.h"
#include "CustomerManagement.h"
#include "AdminManagement.h"
#include "SupplierRequestManagement.h"
#include "Customer.h"
#include "SupplierRequest.h"

using namespace std;

class MainMenu {
private:
    CarManagement carManager;
    CustomerManagement customerManager;
    AdminManagement adminManager;
    SupplierRequestManagement requestManager;

    // Helper functions for input validation
    bool isValidPhone(const string& phone);
    bool isValidName(const string& name);

    void newCarManagementMenu();
    void oldDomesticCarManagementMenu();
    void foreignCarManagementMenu();

    // Car purchase related methods
    void handleNewCarPurchase(Customer& customer);
    void handleOldCarPurchase(Customer& customer);
    void handleForeignCarPurchase(Customer& customer);
    void performCarPurchase(Customer& customer);
    void displayCustomerRequests(const Customer& customer);
    bool validateYear(int year, int minYear, int maxYear);
    void createPurchaseRequest(Customer& customer, const string& model, int year,
                               const string& specs, const string& condition, double price);

public:
    MainMenu();
    void showMenu();

private:
    void adminLogin();
    void registerAdmin();
    void customerLogin();
    void displayUserManual();
    void adminMenu();
    void carManagementMenu();
    void customerManagementMenu();
    void supplierRequestMenu();
    void customerMenu(Customer& customer);
    void handleCarPurchase(Customer& customer);
};

#endif //COURSEWORKAVTO_MAINMENU_H