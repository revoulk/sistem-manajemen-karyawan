#ifndef AUTH_H
#define AUTH_H

#include <string>
#include "User.h"

class Auth {
public:
    // Login: cari user dengan username & password cocok
    static User* login(const std::string& username, const std::string& password);

    // Register: tambah user baru sebagai 'user' (default)
    static bool registerUser(const std::string& username, const std::string& password);
};

#endif
