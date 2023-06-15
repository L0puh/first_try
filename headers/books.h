#ifndef BOOKS_H
#define BOOKS_H
#include<iostream>
#include"sqlite3.h"
#include<sstream>

struct book_t{
    std::string title;
    std::string author;
    int price;
};

class Book {
    private:
        book_t book; 
    public:
        book_t get_new_book();
};

#endif 
