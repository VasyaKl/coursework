#ifndef COURSEWORKAVTO_ADMINMANAGEMENT_H
#define COURSEWORKAVTO_ADMINMANAGEMENT_H

#include "Admin.h"
#include <vector>
#include <string>
#include <fstream>
#include <regex>

using namespace std;

class AdminManagement {
private:
    vector<Admin> admins;
    const string ADMIN_FILE = "admins.txt";
    bool isFirstRun();

public:
    AdminManagement();
    void loadAdminsFromFile(const string& filename);
    void saveAdminsFromFile(const string& filename) const;
    bool registerAdmin(const string& username, const string& password);
    bool login(const string& username, const string& password);
    bool canRegisterAdmin() const; // New method

private:
    bool isValidName(const string& name);
    bool isValidPassword(const string& password);
};

#endif
