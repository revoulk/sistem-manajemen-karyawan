#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User {
public:
    Admin(int id, const std::string& username, const std::string& password);

    void tampilkanSemuaUser() const;
    void cariUserById(int id) const;
    void tambahUser();
    void editUser(int id);
    void hapusUser(int id);
};

#endif