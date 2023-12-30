/*
counts same characters in
two strings using
dynamic programming
 */

#include <iostream>



int main() {
    int x, y;
    std::string n, m;
    std::cin >> x >> y >> n >> m;
    
    int word[x][y];
    int max = 0;

    for (int i = 0; i != y; i++){
        if (n[i] == m[0])
            word[0][i] = 1;
        else word[0][i] = 0;
    }

    for (int i = 0; i != x; i++){
        if (n[0] == m[i])
            word[i][0] = 1;
        else word[i][0] = 0;
    }

    for (int i = 1; i != x; i++){
        for (int j = 1; j != y; j++){
            if (n[i] == m[j]) 
                word[i][j] = word[i-1][j-1] + 1;
            else 
                word[i][j] = std::max(word[i-1][j], word[i][j-1]);
            if (word[i][j] > max) 
                max = word[i][j];
        }
    }

    printf("%d chs are same\n", max);
}
