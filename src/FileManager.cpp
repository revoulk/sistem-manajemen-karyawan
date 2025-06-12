#include "../includes/FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<User> FileManager::readUsers() {
    std::vector<User> users;
    std::ifstream file("data/users.txt");
    if (!file.is_open()) {
        std::cerr << "Gagal membuka file users.txt\n";
        return users;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, username, password, role;

        std::getline(ss, id, ';');
        std::getline(ss, username, ';');
        std::getline(ss, password, ';');
        std::getline(ss, role, ';');

        User user(std::stoi(id), username, password, role);
        users.push_back(user);
    }

    file.close();
    return users;
}

void FileManager::writeUsers(const std::vector<User>& users) {
    std::ofstream file("data/users.txt", std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Gagal menulis ke file users.txt\n";
        return;
    }

    for (const auto& user : users) {
        file << user.getId() << ";"
             << user.getUsername() << ";"
             << user.getPassword() << ";"
             << user.getRole() << "\n";
    }

    file.close();
}
