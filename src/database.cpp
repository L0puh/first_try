#include "../headers/database.h"

sqlite3 *DB;
const char dbfile[] = {"users.db"};

int connect_db(){
    int connect = sqlite3_open(dbfile, &DB );
    
    if(connect){
        std::cerr << "error: " << sqlite3_errmsg(DB) << std::endl;
        return -1; 
    }
    else
        sqlite3_close(DB);
   
    return 0;
}

int create_table(){
    int connect = sqlite3_open(dbfile, &DB);
    
    std::string sql = "CREATE TABLE users(id INT PRIMARY KEY NOT NULL, name TEXT, password INT);";
    
    char* error_message;
    connect = sqlite3_exec(DB, sql.c_str(), NULL, 0, &error_message);
    
    if (connect != SQLITE_OK)
        std::cerr << "Error Create Table: " << error_message  << std::endl;
    
    sqlite3_close(DB);
    return (0);
}


