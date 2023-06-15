#include "../headers/books.h"


book_t Book::get_new_book (){
    std::cout << "Enter title" << std::endl << '>';
    getline(std::cin >> std::ws, book.title);
    
    std::cout << "Enter author" << std::endl << '>';
    getline(std::cin >> std::ws, book.author);

    std::cout << "Enter price" << std:: endl << '>';
    std::cin >> book.price;
    
    return book; 
}
