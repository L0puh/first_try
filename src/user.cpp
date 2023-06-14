#include "../headers/user.h"


std::string get_login(){
    std::string login;
    std::cout << "enter your login" << '\n' << ">";
    std::cin >> login;
    return login;
}
int get_password(){
    int password;
    std::cout << "enter your password" << '\n' << ">";
    std::cin >> password;
    return password; 
}

user_s get_user(){
    user_s user;
    user.login = get_login();
    user.password = get_password();
    return user;
}
