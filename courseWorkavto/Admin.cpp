#include "Admin.h"

#include <utility>

Admin::Admin() = default;

Admin::Admin(string u, string p) : username(std::move(u)), password(std::move(p)) {}

string Admin::getUsername() const { return username; }
string Admin::getPassword() const { return password; }

void Admin::fromCSV(const string& line) {
    stringstream ss(line);
    string token;
    getline(ss, token, ',');
    username = token;
    getline(ss, token, ',');
    password = token;
}

string Admin::toCSV() const {
    return username + "," + password;
}

