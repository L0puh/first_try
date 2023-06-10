#include <iostream>
#include "headers/books.h"
#include "headers/user.h"

void action();

int main(){
    std::string login; int password;
    do {
    login = get_login();
    password = get_password();
    }
    while (!check_login(login, password));
    action();
    return 0;
}

void action(){
    int choice;
    std::cout << "What you're going to do?(1 - create book, 2 - list all books)" << std::endl;
    std::cin >> choice;
    switch (choice){
        case 1: 
            create_book(); break;
        case 2: 
            list_books(); break;
        default:
            std::cout << "There's not that option";
    }

}
