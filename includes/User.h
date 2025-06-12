#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
protected:
    int id;
    std::string username;
    std::string password;
    std::string role;

public:
    User();
    User(int id, const std::string& username, const std::string& password, const std::string& role);

    int getId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getRole() const;

    void setId(int id);
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setRole(const std::string& role);

    void editAkun(std::vector<User>& allUsers);
};

#endif
