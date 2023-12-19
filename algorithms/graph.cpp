#include <map>
#include <queue>
#include <string>
#include <vector>

typedef std::pair<std::string, std::vector<std::string>> dict;

void push_all(std::vector<std::string> ppl, std::queue<std::string> *q){
    for (const auto& p: ppl){
        q->push(p);
    }
}

bool search_exists(std::vector<std::string> s, std::string name) {
    for(const auto& c: s){
        if (c == name) return true;
    }
    return false;
}

void check(std::string name){
    printf("check for %s...", name.c_str());
}

int main() {
    std::string seller = "Ken";
    std::map<std::string, std::vector<std::string>> people{
        {"you", {"Alice", "Tom"}},
        {"Alice", {"Magie"}},
        {"Tom", {"Daniel", "Clara"}},
        {"Clara", {"Alice", "Ken"}},
        {"Magie", {"you"}},
        {"Daniel", {}},
        {"Ken", {}}
    };

    std::queue<std::string> search_engine;
    push_all(people.at("you"), &search_engine);
    std::vector<std::string> search_ppl;

    while (!search_engine.empty()){
        std::string p = search_engine.front();
        search_engine.pop();
        if (search_exists(search_ppl, p)) continue;
        check(p);
        if (p == seller){
            printf("%s is a seller\n", p.c_str());
            return 0;
        }
        push_all(people.at(p), &search_engine);
        search_ppl.push_back(p);
    }
    return 0;
}
