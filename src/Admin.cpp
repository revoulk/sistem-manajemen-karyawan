#include "../includes/Admin.h"
#include "../includes/FileManager.h"
#include "../includes/Absensi.h"
#include <iostream>

Admin::Admin(int id, const std::string& username, const std::string& password)
    : User(id, username, password, "admin") {}

void Admin::tampilkanSemuaUser() const {
    std::vector<User> users = FileManager::readUsers();
    std::cout << "\n--- Daftar Semua User ---\n";
    for (const auto& user : users) {
        std::cout << "ID: " << user.getId()
                  << ", Username: " << user.getUsername()
                  << ", Role: " << user.getRole() << "\n";
    }
}

void Admin::cariUserById(int targetId) const {
    std::vector<User> users = FileManager::readUsers();
    bool ditemukan = false;

    for (const auto& user : users) {
        if (user.getId() == targetId) {
            std::cout << "\n=== Data User ===\n";
            std::cout << "ID      : " << user.getId() << "\n";
            std::cout << "Username: " << user.getUsername() << "\n";
            std::cout << "Role    : " << user.getRole() << "\n";

            ditemukan = true;
            Absensi::tampilkanLogByUserId(user.getId());
            break;
        }
    }

    if (!ditemukan) {
        std::cout << "User dengan ID tersebut tidak ditemukan.\n";
    }
}

void Admin::tambahUser() {
    std::vector<User> users = FileManager::readUsers();
    std::string username, password;

    std::cout << "\n=== Tambah User Baru ===\n";
    std::cout << "Username: ";
    std::getline(std::cin, username);
    std::cout << "Password: ";
    std::getline(std::cin, password);

    for (const auto& u : users) {
        if (u.getUsername() == username) {
            std::cout << "Username sudah digunakan.\n";
            return;
        }
    }

    int newId = users.empty() ? 1 : users.back().getId() + 1;
    User newUser(newId, username, password, "user");
    users.push_back(newUser);
    FileManager::writeUsers(users);
    std::cout << "User berhasil ditambahkan.\n";
}

void Admin::editUser(int targetId) {
    std::vector<User> users = FileManager::readUsers();
    bool ditemukan = false;

    for (auto& user : users) {
        if (user.getId() == targetId && user.getRole() != "admin") {
            int opsi;
            std::string inputBaru;

            std::cout << "\n=== Edit User ID: " << targetId << " ===\n";
            std::cout << "1. Edit Username\n";
            std::cout << "2. Edit Password\n";
            std::cout << "0. Batal\n";
            std::cout << "Pilih: ";
            std::cin >> opsi;
            std::cin.ignore();

            if (opsi == 1) {
                std::cout << "Username baru: ";
                std::getline(std::cin, inputBaru);

                for (const auto& u : users) {
                    if (u.getId() != targetId && u.getUsername() == inputBaru) {
                        std::cout << "Username sudah digunakan oleh user lain.\n";
                        return;
                    }
                }
                user.setUsername(inputBaru);
                std::cout << "Username berhasil diperbarui.\n";

            } else if (opsi == 2) {
                std::cout << "Password baru: ";
                std::getline(std::cin, inputBaru);
                user.setPassword(inputBaru);
                std::cout << "Password berhasil diperbarui.\n";

            } else if (opsi == 0) {
                std::cout << "Edit dibatalkan.\n";
                return;
            } else {
                std::cout << "Pilihan tidak valid.\n";
                return;
            }

            FileManager::writeUsers(users);
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        std::cout << "User tidak ditemukan atau merupakan admin.\n";
    }
}

void Admin::hapusUser(int targetId) {
    std::vector<User> users = FileManager::readUsers();
    bool dihapus = false;

    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->getId() == targetId && it->getRole() != "admin") {
            users.erase(it);
            FileManager::writeUsers(users);
            std::cout << "User berhasil dihapus.\n";
            dihapus = true;
            break;
        }
    }

    if (!dihapus) {
        std::cout << "User tidak ditemukan atau merupakan admin.\n";
    }
}