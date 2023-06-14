#include "../headers/database.h"
#include <sstream>
sqlite3 *DB;
const char dbfile[] = {"users.db"};

static int printback(void* sql_data, int rows, char** data, char** colum_name)
{
    fprintf(stderr, "%s: ", (const char*)sql_data);
    for (int i = 0; i < rows; i++) 
        printf("%s = %s\n", colum_name[i], data[i]);
    return 0;
}

static int callback(void* sql_data, int rows, char** data, char** colum_name){
    if (data)
        return 1;
    return 0;
}

int connect_db(){
    int connect = sqlite3_open(dbfile, &DB );
    
    if(connect){
        std::cerr << "error: " << sqlite3_errmsg(DB) << std::endl;
        return -1; 
    }
   
    return connect;
}

bool check_user(std::string data, int password){
    int connect = connect_db();

    std::stringstream s;
    s << "SELECT * FROM users WHERE name = " <<  "'" << data << "' AND password = " <<  password << ";";
    std::string sql = s.str();
    
    connect = sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL); 
    sqlite3_close(DB);
    if (connect)
        return false;
    return true;
}


int create_table(){
    int connect = connect_db(); 
    std::string sql = "CREATE TABLE users(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, password INTEGER);";
    /* std::string sql = "CREATE TABLE books(id INTEGER PRIMARY KEY AUTOINCREMENT, titile TEXT, author TEXT, price INT)"; */
    char* error_message;
    connect = sqlite3_exec(DB, sql.c_str(), NULL, 0, &error_message);
    
    if (connect != SQLITE_OK)
        std::cerr << "error create table: " << error_message  << std::endl;
    
    sqlite3_close(DB);
    return (0);
}

int list_books(){
    int connect = connect_db();
    std::string sql = "SELECT * FROM books";
    char* error_message;
    connect = sqlite3_exec(DB, sql.c_str(), printback, 0, &error_message);
    if (connect != SQLITE_OK)
        std::cerr << "error list books: " << error_message << std::endl;
    sqlite3_close(DB);
    return 0;
}

int create_book(book bk){
    int connect = connect_db();
    std::stringstream s;
    s << "INSERT INTO books VALUES(NULL, '" << bk.title << "','"<< bk.author << "'," << bk.price << ");" ;
    std::string sql = s.str();
    char* error_message;
    connect = sqlite3_exec(DB, sql.c_str(), NULL, 0, &error_message);
    if (connect != SQLITE_OK)
        std::cerr << "error create book: " << error_message << std::endl;
    sqlite3_close(DB);
    return 0;

}

int create_user(std::string login, int password){
    int connect = connect_db();
    std::stringstream s; 
    s << "INSERT INTO users VALUES(NULL, '" << login << "', " << password << ");";
    std::string sql = s.str();
    char* error_message;
    connect = sqlite3_exec(DB, sql.c_str(), NULL, 0, &error_message);
    if (connect != SQLITE_OK){
            std::cout << "error create user: " << error_message << '\n';
    }
    return 0;
}

