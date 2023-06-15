cmake_minimum_required(VERSION 0.1)
project(books)
add_executable(books 
    main.cpp
    src/user.cpp 
    src/books.cpp 
    src/database.cpp  
) 
target_link_libraries(books -lsqlite3)
