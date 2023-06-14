#include <iostream>
#include "headers/books.h"
#include "headers/user.h"
#include "headers/database.h"

bool action(user_s user);
int main(){
    //TODO: refactoring
    int choice;
    bool result=true;
    user_s user = get_user();
    do {  
        result = check_user(user.login, user.password);
        if (result){
            std::cout << "repeat (1) or create new account(2)?" << '\n' << '>' ;
            std::cin >> choice;
            switch(choice){
                case 1:
                    user = get_user();
                    break;
                case 2: 
                    create_user(user.login, user.password);
                    goto created_user;
            }
        }
    } while (result); 
   
    created_user:
    while(action(user)) 
        continue;
    return 0;
}

bool action(user_s user){
    int choice;
    std::cout << user.login << ", your options: create book(1), list all books(2), exit(3)" << std::endl;
    std::cin >> choice;
    switch (choice){
        case 1: 
            create_book(get_new_book()); break;
        case 2: 
            list_books(); break;
        case 3:
            return false; 
        default:
            std::cout << "There's not that option\n";
    }
    return true;
}
