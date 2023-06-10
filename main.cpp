#include <iostream>
#include "headers/books.h"
#include "headers/user.h"

bool action();

int main(){
    std::string login; int password;
    do {
    login = get_login();
    password = get_password();
    }
    while (!check_login(login, password));
    
    while (action()){
        action();
    }

    return 0;
}

bool action(){
    int choice;
    std::cout << "What are you going to do?(create book(1), list all books(2), exit(3))" << std::endl;
    std::cin >> choice;
    switch (choice){
        case 1: 
            create_book(); break;
        case 2: 
            list_books(); break;
        case 3:
            return false; 
        default:
            std::cout << "There's not that option";
    }
    return true;
}
