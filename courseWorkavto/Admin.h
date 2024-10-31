#ifndef COURSEWORKAVTO_ADMIN_H
#define COURSEWORKAVTO_ADMIN_H

#include <string>
#include <sstream>
using namespace std;

class Admin {
private:
    string username;
    string password;

public:
    Admin();
    Admin(string u, string p);

    string getUsername() const;
    string getPassword() const;

    void fromCSV(const string& line);
    string toCSV() const;
};

#endif //COURSEWORKAVTO_ADMIN_H
