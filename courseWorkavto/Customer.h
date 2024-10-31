#ifndef COURSEWORKAVTO_CUSTOMER_H
#define COURSEWORKAVTO_CUSTOMER_H

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Customer {
private:
    static int nextId;
    int customerId;
    string lastName;
    string firstName;
    string patronymic;
    string phone;
    string country;
    string city;
    vector<int> purchasedCarIds;

public:
    Customer();
    Customer(string ln, string fn, string p, string ph, string c, string ci);

    // Getters
    int getCustomerId() const;
    string getLastName() const;
    string getFirstName() const;
    string getPatronymic() const;
    string getPhone() const;
    string getCountry() const;
    string getCity() const;
    const vector<int>& getPurchasedCarIds() const;

    // Setters
    void setCustomerId(int id);

    // Other methods
    void addPurchasedCar(int carId);
    string getName() const;
    void display() const;
    string toCSV() const;
    void fromCSV(const string& data);
    void displayProfile() const;



};

#endif //COURSEWORKAVTO_CUSTOMER_H
