#include <iostream>

struct item {
    int weight;
    int value;
};



int main() {
    int w, v, max, size, mix;
    item knapsack[size];
    std::cin >> max >> size;

    for (int i = 0; i != size; i++){
        std::cin >>  w >> v;
        knapsack[i] = {w, v};
    }

    int grid[size+1][max+1];
    for (int i = 0; i <= size; i++){
        for (int j = 0; j <= max; j++){
            if (i == 0 || j == 0) 
                grid[i][j] = 0;

            else if (knapsack[i-1].weight <= j){
                mix = knapsack[i-1].value + grid[i-1][j - knapsack[i-1].weight],
                grid[i][j] = std::max(mix, grid[i-1][j]); // maximum of the current item + with item less weight
                                                          // vs previous item 
            }
            else grid[i][j] = grid[i-1][j];
        }
    }

    printf("%d\n", grid[size][max]);
    return 0;
}
