#ifndef COURSEWORKAVTO_OLDDOMESTICCAR_H
#define COURSEWORKAVTO_OLDDOMESTICCAR_H

#include <string>

class OldDomesticCar {
private:
    int id;
    std::string brand;
    int year;
    std::string specifications;
    std::string color;
    std::string condition;
    double price;
    bool sold;

public:
    OldDomesticCar();
    OldDomesticCar(int id, const std::string& brand, int year, const std::string& specifications,
                   const std::string& color, double price, const std::string& condition);

    // Getters
    int getId() const;
    std::string getBrand() const;
    int getYear() const;
    std::string getSpecifications() const;
    std::string getColor() const;
    double getPrice() const;
    bool isSold() const;
    std::string getCondition() const;

    // Setters
    void setId(int i);
    void setBrand(std::string b);
    void setYear(int y);
    void setSpecifications(std::string s);
    void setColor(std::string c);
    void setPrice(double p);
    void setSold(bool s);
    void setCondition(const std::string& newCondition);

    void display() const;
    std::string toCSV() const;
    void fromCSV(const std::string& data);
};

#endif //COURSEWORKAVTO_OLDDOMESTICCAR_H
