#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include "sqlite3.h"
#include "../headers/books.h"

int create_table();
int connect_db();
int create_book(book bk);
bool check_user(std::string name, int password);
int list_books();
int create_user(std::string login, int password);
#endif
