#ifndef ABSENSI_H
#define ABSENSI_H

#include "User.h"

class Absensi {
public:
    static void absenMasuk(const User& user);
    static void tampilkanLogAbsensi();
    static void tampilkanLogByUserId(int userId);
};

#endif