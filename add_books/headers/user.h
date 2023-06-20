#ifndef USER_H
#define USER_H
#include <iostream>

struct user_s {
    std::string login;
    int password;
};

int get_password();
std::string get_login();
user_s get_user();

#endif
