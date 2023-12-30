#include <algorithm>
#include <iterator>
#include <set>
#include <cstdio>
#include <string>
#include <vector>

void print_set(std::vector<std::string> s, std::string str){
    for (auto& i: s){
        printf("%s: %s\n", str.c_str(), i.c_str());
    }
    printf("\n");
}

void print_set(std::set<std::string> s, std::string str){
    for (auto& i: s){
        printf("%s: %s\n", str.c_str(), i.c_str());
    }
    printf("\n");
}


int main () {
    std::set<std::string> 
        fruits{"tomato", "avocado", "banana"}, 
        vegetables{"tomato", "beans", "carrots"};

    print_set(fruits, "fruits");
    print_set(vegetables, "vegetables");

    std::vector<std::string> intersection, difference, union_set;

    std::set_intersection(fruits.begin(), fruits.end(), 
                          vegetables.begin(), vegetables.end(), 
                          std::back_inserter(intersection));

    std::set_difference(fruits.begin(), fruits.end(), 
                          vegetables.begin(), vegetables.end(), 
                          std::back_inserter(difference));

    std::set_union(fruits.begin(), fruits.end(), 
                          vegetables.begin(), vegetables.end(),
                          std::back_inserter(union_set));

    print_set(intersection, "intersection of fruits");
    print_set(difference, "difference");
    print_set(union_set, "union");
    

    return 0;
}
