#include <iostream>
#include <vector>
#include "includes/User.h"
#include "includes/FileManager.h"
#include "includes/Auth.h"
#include "includes/Admin.h"
#include "includes/Absensi.h"

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    int choice;
    std::string username, password;

    while (true) {
        std::cout << "\n===== MENU UTAMA =====\n";
        std::cout << "1. Register (user)\n";
        std::cout << "2. Login\n";
        std::cout << "0. Keluar\n";
        std::cout << "Pilih: ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            std::cout << "Username: ";
            std::getline(std::cin, username);
            std::cout << "Password: ";
            std::getline(std::cin, password);
            Auth::registerUser(username, password);

        } else if (choice == 2) {
            std::cout << "Username: ";
            std::getline(std::cin, username);
            std::cout << "Password: ";
            std::getline(std::cin, password);

            User* loggedIn = Auth::login(username, password);
            if (loggedIn != nullptr) {
                clearScreen();
                std::cout << "Login berhasil sebagai: " << loggedIn->getRole() << "\n";
                std::cout << "Selamat datang, " << loggedIn->getUsername() << "!\n";

                bool sudahAbsen = false;
                std::vector<User> allUsers = FileManager::readUsers();

                if (loggedIn->getRole() == "admin") {
                    Admin admin(loggedIn->getId(), loggedIn->getUsername(), loggedIn->getPassword());
                    int adminChoice;
                    while (true) {
                        std::cout << "\n--- Menu Admin ---\n";
                        std::cout << "1. Tampilkan semua user\n";
                        std::cout << "2. Lihat log absensi\n";
                        std::cout << "3. Absen Masuk\n";
                        std::cout << "4. Edit akun sendiri\n";
                        std::cout << "5. Cari user berdasarkan ID\n";
                        std::cout << "6. Tambah user\n";
                        std::cout << "7. Edit user (non-admin)\n";
                        std::cout << "8. Hapus user (non-admin)\n";
                        std::cout << "0. Logout\n";
                        std::cout << "Pilih: ";
                        std::cin >> adminChoice;
                        std::cin.ignore();

                        if (adminChoice == 1) {
                            admin.tampilkanSemuaUser();
                        } else if (adminChoice == 2) {
                            Absensi::tampilkanLogAbsensi();
                        } else if (adminChoice == 3) {
                            if (!sudahAbsen) {
                                Absensi::absenMasuk(admin);
                                sudahAbsen = true;
                            } else {
                                std::cout << "Anda sudah absen dalam sesi ini.\n";
                            }
                        } else if (adminChoice == 4) {
                            admin.editAkun(allUsers);
                        } else if (adminChoice == 5) {
                            int cariId;
                            std::cout << "Masukkan ID user: ";
                            std::cin >> cariId;
                            std::cin.ignore();
                            admin.cariUserById(cariId);
                        } else if (adminChoice == 6) {
                            admin.tambahUser();
                        } else if (adminChoice == 7) {
                            int editId;
                            std::cout << "Masukkan ID user yang akan diedit: ";
                            std::cin >> editId;
                            std::cin.ignore();
                            admin.editUser(editId);
                        } else if (adminChoice == 8) {
                            int hapusId;
                            std::cout << "Masukkan ID user yang akan dihapus: ";
                            std::cin >> hapusId;
                            std::cin.ignore();
                            admin.hapusUser(hapusId);
                        } else if (adminChoice == 0) {
                            std::cout << "Logout berhasil.\n";
                            break;
                        } else {
                            std::cout << "Pilihan tidak valid.\n";
                        }
                    }

                } else if (loggedIn->getRole() == "user") {
                    int userChoice;
                    while (true) {
                        std::cout << "\n--- Menu User ---\n";
                        std::cout << "1. Absen Masuk\n";
                        std::cout << "2. Edit Akun\n";
                        std::cout << "0. Logout\n";
                        std::cout << "Pilih: ";
                        std::cin >> userChoice;
                        std::cin.ignore();

                        if (userChoice == 1) {
                            if (!sudahAbsen) {
                                Absensi::absenMasuk(*loggedIn);
                                sudahAbsen = true;
                            } else {
                                std::cout << "Anda sudah absen dalam sesi ini.\n";
                            }
                        } else if (userChoice == 2) {
                            loggedIn->editAkun(allUsers);
                        } else if (userChoice == 0) {
                            std::cout << "Logout berhasil.\n";
                            break;
                        } else {
                            std::cout << "Pilihan tidak valid.\n";
                        }
                    }
                }

                delete loggedIn;
                clearScreen();

            } else {
                std::cout << "Login gagal. Username/password salah.\n";
            }

        } else if (choice == 0) {
            std::cout << "Program selesai.\n";
            break;
        } else {
            std::cout << "Pilihan tidak valid.\n";
        }
    }

    return 0;
}