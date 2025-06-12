#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>
#include "../includes/User.h"

class FileManager {
public:
    // Membaca semua user dari file users.txt
    static std::vector<User> readUsers();

    // Menulis semua user ke file users.txt
    static void writeUsers(const std::vector<User>& users);
};

#endif
