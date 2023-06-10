#include "../headers/user.h"

const std::string f = "users.txt";

bool check_login(std::string login, int password){
    user users;
    std::string line;
    std::ifstream file(f);
    bool is_login=false; 

    while (getline(file, line)){
        if (line != "" && typeid(line) == typeid(std::string) && !is_login) {
            if (line == login){
                is_login=true;
            } 
        } else if (line != "" && is_login && isNumber(line)){
            users.password = stoi(line);
            break;
        }
    }

    bool res = check_password(users, password);
    file.close();
    return res;
}


bool check_password(user users, int password){
    if (users.password == password){
        std::cout << "your password is right" << std::endl;
        return true;
    }
    std::cout << "your password is wrong" << std::endl;
    return false;
}

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


bool isNumber(const std::string s)
{
    for (char const &ch : s) {
        if (isdigit(ch) == 0) 
            return false;
    }
    return true;
}
