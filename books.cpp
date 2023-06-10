#include "books.h"
const std::string file = "books.txt";

void list_books(){
    std::ifstream f(file);
    std::string line;
    while (getline(f, line)){
        std::cout << line << std::endl;
    }
}
book create_book(){
    using namespace std;

    book bk;

    cout << "Enter title" << endl << '>';
    getline(cin >> ws, bk.title);
    
    cout << "Enter author" << endl << '>';
    getline(cin >> ws, bk.author);

    cout << "Enter price" << endl << '>';
    cin >> bk.price;
    
    ofstream f(file, ofstream::app);
    f << bk.title << '\n' << bk.author << '\n' << bk.price << "\n\n";
    cout << "Book've created" << endl;
    return bk; 
}

