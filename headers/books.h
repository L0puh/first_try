#ifndef BOOKS_H
#define BOOKS_H
#include<iostream>
#include<fstream>

typedef struct {
    std::string title;
    std::string author;
    int price;
} book;

book create_book();
void list_books();

#endif 
