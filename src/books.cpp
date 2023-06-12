#include "../headers/books.h"

book get_new_book(){
    using namespace std;

    book bk;

    cout << "Enter title" << endl << '>';
    getline(cin >> ws, bk.title);
    
    cout << "Enter author" << endl << '>';
    getline(cin >> ws, bk.author);

    cout << "Enter price" << endl << '>';
    cin >> bk.price;
    
    cout << "Book've created" << endl;
    return bk; 
}

