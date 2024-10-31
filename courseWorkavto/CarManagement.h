#ifndef COURSEWORKAVTO_CARMANAGEMENT_H
#define COURSEWORKAVTO_CARMANAGEMENT_H

#include "NewCar.h"
#include "OldDomesticCar.h"
#include "ForeignCar.h"
#include <vector>
#include <string>

using namespace std;

class CarManagement {
private:
    vector<NewCar> newCars;
    vector<OldDomesticCar> oldDomesticCars;
    vector<ForeignCar> foreignCars;
    int nextNewId;
    int nextOldId;
    int nextForeignId;
    int loadedCount;

    template<typename T>
    bool carExists(const vector<T>& cars, int id) const;



public:
    CarManagement() : nextNewId(1), nextOldId(1), nextForeignId(1), loadedCount(0) {
        newCars.clear();
        oldDomesticCars.clear();
        foreignCars.clear();

        loadCarsFromFile("newcars.txt");
        loadCarsFromFile("oldcars.txt");
        loadCarsFromFile("foreigncars.txt");
    }



    // Add methods
    void addNewCar(NewCar& car);
    void addOldDomesticCar(OldDomesticCar& car);
    void addForeignCar(ForeignCar& car);

    // Display methods
    void displayCars(bool onlyNew = false) const;
    void displayNewCars() const;
    void displayOldDomesticCars() const;
    void displayForeignCars() const;
    void displayAvailableCars() const;

    // Find methods
    NewCar* findNewCarById(int id);
    OldDomesticCar* findOldDomesticCarById(int id);
    ForeignCar* findForeignCarById(int id);

    // Count methods
    int getNewCarsCount() const { return newCars.size(); }
    int getOldDomesticCarsCount() const { return oldDomesticCars.size(); }
    int getForeignCarsCount() const { return foreignCars.size(); }
    int getTotalCarsCount() const { return newCars.size() + oldDomesticCars.size() + foreignCars.size(); }

    // Delete methods
    bool deleteNewCar(int id);
    bool deleteOldDomesticCar(int id);
    bool deleteForeignCar(int id);
    void removeCar(const string& filename, int id);


    // File operations
    void saveCarsToFile(const char* filename) const;
    void loadCarsFromFile(const string& filename);


    // Sales operation
    void sellCar(int id);

    template<typename T>
    vector<T*> findMatchingCarsInVector(vector<T>& cars, const string& brand, int yearFrom, int yearTo,
                                        const string& condition, double minPrice, double maxPrice);

    vector<NewCar*> findMatchingCar(const string& brand, int yearFrom, int yearTo,
                                    const string& condition, double minPrice, double maxPrice);

    vector<OldDomesticCar*> findMatchingOldCars(const string& brand, int yearFrom, int yearTo,
                                                const string& condition, double minPrice, double maxPrice);

    vector<ForeignCar*> findMatchingForeignCars(const string& brand, int yearFrom, int yearTo,
                                                const string& condition, double minPrice, double maxPrice);
};
#endif //COURSEWORKAVTO_CARMANAGEMENT_H

