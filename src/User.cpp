#include "../includes/User.h"
#include "../includes/FileManager.h"
#include <iostream>

User::User() : id(0), username(""), password(""), role("") {}

User::User(int id, const std::string& username, const std::string& password, const std::string& role)
    : id(id), username(username), password(password), role(role) {}

int User::getId() const { return id; }
std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
std::string User::getRole() const { return role; }

void User::setId(int newId) { id = newId; }
void User::setUsername(const std::string& newUsername) { username = newUsername; }
void User::setPassword(const std::string& newPassword) { password = newPassword; }
void User::setRole(const std::string& newRole) { role = newRole; }

void User::editAkun(std::vector<User>& allUsers) {
    int opsi;
    std::string inputBaru;

    std::cout << "\n=== Edit Akun ===\n";
    std::cout << "1. Ubah Username\n";
    std::cout << "2. Ubah Password\n";
    std::cout << "0. Batal\n";
    std::cout << "Pilih: ";
    std::cin >> opsi;
    std::cin.ignore();

    if (opsi == 1) {
        std::cout << "Username baru: ";
        std::getline(std::cin, inputBaru);

        for (const auto& u : allUsers) {
            if (u.getId() != this->id && u.getUsername() == inputBaru) {
                std::cout << "Username sudah digunakan oleh user lain.\n";
                return;
            }
        }

        this->username = inputBaru;
        for (auto& u : allUsers) {
            if (u.getId() == this->id) {
                u.setUsername(inputBaru);
                break;
            }
        }

        std::cout << "Username berhasil diperbarui.\n";

    } else if (opsi == 2) {
        std::cout << "Password baru: ";
        std::getline(std::cin, inputBaru);

        this->password = inputBaru;
        for (auto& u : allUsers) {
            if (u.getId() == this->id) {
                u.setPassword(inputBaru);
                break;
            }
        }

        std::cout << "Password berhasil diperbarui.\n";

    } else if (opsi == 0) {
        std::cout << "Edit dibatalkan.\n";
        return;

    } else {
        std::cout << "Pilihan tidak valid.\n";
        return;
    }

    FileManager::writeUsers(allUsers);
}
