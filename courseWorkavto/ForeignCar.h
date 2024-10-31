#ifndef COURSEWORKAVTO_FOREIGNCAR_H
#define COURSEWORKAVTO_FOREIGNCAR_H

#include <string>

class ForeignCar {
private:
    int id;
    std::string brand;
    int year{};
    std::string specifications;
    std::string color;
    std::string condition;
    double price{};
    bool sold;
    static bool isEnglishBrand(const std::string& brand);

public:
    ForeignCar();
    ForeignCar(int id, const std::string& brand, int year, const std::string& specifications,
                const std::string& color, double price, const std::string& condition);

    // Getters
    int getId() const;
    std::string getBrand() const;
    int getYear() const;
    std::string getSpecifications() const;
    std::string getColor() const;
    std::string getCondition() const;
    double getPrice() const;
    bool isSold() const;

    // Setters
    void setId(int i);
    void setBrand(std::string b);
    void setYear(int y);
    void setSpecifications(std::string s);
    void setColor(std::string c);
    void setCondition(const std::string& newCondition);
    void setPrice(double p);
    void setSold(bool s);

    void display() const;
    std::string toCSV() const;
    void fromCSV(const std::string& data);


};

#endif //COURSEWORKAVTO_FOREIGNCAR_H

