#include <iostream>
#include <ostream>
#include <map>
#include <vector>


typedef std::vector<std::string> vstring;

class Queue{
    std::map<std::string, vstring> q; 
    public:

        void enqueue(std::string key, vstring value) {
            q[key] = value;
        }
        void enqueue(std::pair<std::string, vstring> pair) {
            q.insert(pair, *(q.begin()));
        }
        std::pair<std::string, vstring> dequeue(){
            std::pair<std::string, vstring> a = *(q.begin());
            q.erase(q.begin());
            return a;
        }
        void print_queue(){
            for (const auto& c: q){
                for (const auto& v: c.second){
                    printf("%s : %s\n", c.first.c_str(), v.c_str());
                }
            }
        }
        std::map<std::string, vstring> get_queue(){
            return q;
        }

};

int main(){
    Queue q; 
    std::pair<std::string, vstring> you("you", {"Tom", "Magie", "Marie"});
    q.enqueue(you);
    std::pair<std::string, vstring> Tom("Tom", {"Clarie", "Daniel"});
    q.enqueue(Tom);
    q.print_queue();
    
    
    return 0;
}
