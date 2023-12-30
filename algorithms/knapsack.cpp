#include <algorithm>
#include <iostream>
#include <vector>


struct item {
    int weight;
    int value;
};

int main() {
    std::vector<item> knapsack;
    int w, v, max;
    std::cin >> max;
    for (int i = 0; i!=3; i++){
        std::cin >>  w >> v;
        knapsack.push_back({w, v});
    }
    int grid[knapsack.size()+1][max+1];

    for (int i = 0; i <= knapsack.size(); i++){
        for (int j = 0; j <= max; j++){
            if (i == 0 or j == 0) grid[i][j] = 0;
            else if (knapsack[i-1].weight <= j){
                grid[i][j] = std::max(knapsack.at(i-1).value + grid[i-1][j - knapsack.at(i-1).weight],
                                     grid[i-1][j]);
            }
            else grid[i][j] = grid[i-1][j];
        }
    }
    printf("%d\n", grid[knapsack.size()][max]);
    return 0;
}



















