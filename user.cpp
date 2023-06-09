#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

typedef struct {
    string title;
    int price;
    string author;
} book;

typedef struct {
    string login;
    int password;
} user; 

int get_password();
string get_login();
bool check_login(string login, int password);
book create_book();
bool check_password(user users, int password);
bool isNumber(string s);

int main(){
    string login; int password;
    do {
    login = get_login();
    password = get_password();}
    while (!check_login(login, password));
    book bk = create_book();
    return 0;
}

book create_book(){
    book bk;
    cin >> bk.title; cin >> bk.author; cin >> bk.price;
    ofstream file("books.txt");
    file << bk.title << '\n' << bk.author << '\n' << bk.price;
    cout << "Book've created" << endl;
    return bk; 
}


bool check_login(string login, int password){
    user users;
    string line;
    ifstream file("users.txt");
    bool is_login=false; 

    while (getline(file, line)){
        if (line != "" && typeid(line) == typeid(string) && !is_login) {
            if (line == login){
                is_login=true;
            } 
        } else if (line != "" && is_login && isNumber(line)){
            users.password = stoi(line);
            break;
        }
    }

    bool res = check_password(users, password);
    file.close();
    return res;
}

bool isNumber(const string s)
{
    for (char const &ch : s) {
        if (isdigit(ch) == 0) 
            return false;
    }
    return true;
}

bool check_password(user users, int password){
    if (users.password == password){
        cout << "your password is right" << endl;
        return true;
    }
    cout << "your password is wrong" << endl;
    return false;
}

string get_login(){
    string login;
    cout << "enter your login" << endl << ">";
    cin >> login;
    return login;
}
int get_password(){
    int password;
    cout << "enter your password" << endl << ">";
    cin >> password;
    return password; 
}
