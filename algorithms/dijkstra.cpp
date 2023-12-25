#include <limits>
#include <map>
#include <vector>
#include <cstdio>
#include <string>

const float infinity = std::numeric_limits<float>::infinity();
typedef std::vector<std::pair<std::string, float>> neighbor ;
std::vector<std::string> processed;

void updated(std::map<std::string, float> cost, float new_cost){
    printf("NEW COST: %0.f\n", new_cost);
    for (auto& c:cost) {
        printf("node: %s, cost: %0.f\n", c.first.c_str(), c.second);
    }
    printf("\n\n");
}

bool is_processed(std::string node){
    for (auto& p: processed)
        if (p == node) return true;
    return false;
}

std::string find_lowest_cost(std::map<std::string, float> costs){
    float min = 100;
    std::string node = "";
    for (auto& c: costs){
        if (!is_processed(c.first) and c.second != infinity){
            if (c.second < min){
                min = c.second;
                node = c.first;
            }
        }
    }
    return node;
}


int main() {
    std::map<std::string, neighbor> graph{
        {"start", {{"a", 5}, {"b", 2}}},
        {"a", {{"fin", 2}}},
        {"b", {{"a", 1}, {"fin", 4}}},
        {"fin", {} }
    };
    std::map<std::string, float> costs {
        {"a", 6},
        {"b", 2},
        {"fin", infinity}

    };
    float new_cost = 0;
    std::string node = find_lowest_cost(costs);
    while (node != ""){
        float cost = costs[node];
        neighbor neighbors = graph[node];
        for (const auto& n: neighbors){
            new_cost = cost + n.second;
            if (costs[n.first] > new_cost){
                costs[n.first] = new_cost;
                updated(costs, new_cost);
            }
        }
        processed.push_back(node);
        node = find_lowest_cost(costs);
    }
    printf("ANSWER: %0.f\n", new_cost);
    return 0;
}
