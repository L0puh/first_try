#ifndef USER_H
#define USER_H
#include <iostream>
#include <fstream>

typedef struct {
    std::string login;
    int password;
} user; 

int get_password();
std::string get_login();
bool check_login(std::string login, int password);
bool check_password(user users, int password);
bool isNumber(std::string s);

#endif
