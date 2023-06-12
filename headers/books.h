#ifndef BOOKS_H
#define BOOKS_H
#include<iostream>
#include"sqlite3.h"
#include<sstream>

struct book{
    std::string title;
    std::string author;
    int price;
};

book get_new_book();
/* void list_books(); */

#endif 
