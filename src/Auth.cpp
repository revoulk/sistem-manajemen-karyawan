#include "../includes/Auth.h"
#include "../includes/FileManager.h"
#include <iostream>

User* Auth::login(const std::string& username, const std::string& password) {
    std::vector<User> users = FileManager::readUsers();

    for (auto& user : users) {
        if (user.getUsername() == username && user.getPassword() == password) {
            return new User(user); // login berhasil
        }
    }

    return nullptr; // login gagal
}

bool Auth::registerUser(const std::string& username, const std::string& password) {
    std::vector<User> users = FileManager::readUsers();

    // Cek username duplikat
    for (const auto& user : users) {
        if (user.getUsername() == username) {
            std::cout << "Username sudah digunakan!\n";
            return false;
        }
    }

    // Auto-increment ID dan set role = "user"
    int newId = users.empty() ? 1 : users.back().getId() + 1;
    std::string defaultRole = "user";
    User newUser(newId, username, password, defaultRole);

    users.push_back(newUser);
    FileManager::writeUsers(users);

    std::cout << "Registrasi berhasil sebagai user.\n";
    return true;
}
