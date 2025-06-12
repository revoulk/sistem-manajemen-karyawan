#include "../includes/Absensi.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

void Absensi::absenMasuk(const User& user) {
    std::ofstream file("data/absensi.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Gagal membuka file absensi.txt\n";
        return;
    }

    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    char timeBuffer[20];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", localTime);

    file << user.getId() << ";" << user.getUsername() << ";" << timeBuffer << "\n";
    file.close();

    std::cout << "Absen berhasil pada " << timeBuffer << "\n";
}

void Absensi::tampilkanLogAbsensi() {
    std::ifstream file("data/absensi.txt");
    if (!file.is_open()) {
        std::cerr << "Gagal membuka file absensi.txt\n";
        return;
    }

    std::string line;
    std::cout << "\n--- Log Absensi ---\n";
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, username, timestamp;

        std::getline(ss, id, ';');
        std::getline(ss, username, ';');
        std::getline(ss, timestamp);

        std::cout << "ID: " << id << ", Username: " << username
                  << ", Waktu: " << timestamp << "\n";
    }

    file.close();
}

void Absensi::tampilkanLogByUserId(int userId) {
    std::ifstream file("data/absensi.txt");
    if (!file.is_open()) {
        std::cerr << "Gagal membuka file absensi.txt\n";
        return;
    }

    std::string line;
    bool adaLog = false;

    std::cout << "\n--- Riwayat Absensi ---\n";
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, username, timestamp;

        std::getline(ss, idStr, ';');
        std::getline(ss, username, ';');
        std::getline(ss, timestamp);

        if (std::stoi(idStr) == userId) {
            std::cout << "- " << timestamp << "\n";
            adaLog = true;
        }
    }

    if (!adaLog) {
        std::cout << "(Tidak ada log absensi)\n";
    }

    file.close();
}