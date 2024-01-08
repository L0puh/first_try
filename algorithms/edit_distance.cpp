#include <bits/stdc++.h>


typedef std::vector<std::vector<int>> vi;
int min(int x, int y, int z){
    if (x < y){
        if (x < z) 
            return x;
        else
            return z;
    } else if (y < z)
        return y;
    return z;
}
void print_array(vi v){
    for(int i = 0; i != v.size(); i++){
        for(int j = 0; j != v.at(i).size(); j++){
            if (v[i][j] == INT_MAX){
                printf("? ");
            } else printf("%d ", v[i][j]);
        }
        printf("\n");
    }
}
void fill(vi *grid, int sz1, int sz2){
    for(int i = 0; i != sz1; i++){
        for(int j = 0; j != sz2; j++)
            grid->at(i).push_back(INT_MAX);
    }
}
void swap(int *x, int *y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}
int edit_distance(std::string word1, const std::string word2){
    int size1 = word1.size();
    int size2 = word2.size();
    if (size2 == 0) return size1;
    if (size1 == 0) return size2;

    if(size2 > size1) 
        swap(&size1, &size2);

    vi grid(size1+1);
    fill(&grid, size1+1, size2+1);

    // base cases for empty strings
    for (int i=0; i < size1+1; i++)
        grid[0][i] = i;
    for (int i=0; i < size2+1; i++)
        grid[i][0] = i;

    for (int i = 1; i <= size1; i++ ){
        for (int j = 1; j <= size2; j++){
            if (word1[i-1] == word2[j-1]){
               grid[i][j] = grid[i-1][j-1]; // previous min
            } else {
               grid[i][j] = min(grid[i][j-1],       // insert
                                grid[i-1][j],       // remove 
                                grid[i-1][j-1])+1;  // modify
            }
        }
    }
    print_array(grid);
    return grid[size1][size2];
}

int main(){
    std::string word1, word2;
    std::cin >> word1 >> word2; 
    printf("DISTANCE from %s -> %s: %d\n", word1.c_str(), word2.c_str(), edit_distance(word1, word2));

    return 0;
}
