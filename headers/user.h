#ifndef USER_H
#define USER_H
#include <iostream>

typedef struct {
    std::string login;
    int password;
} user; 

int get_password();
std::string get_login();
#endif
