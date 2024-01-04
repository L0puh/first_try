/*
min cost path (DP)

1. get total sum of the first row
and the first column 
2. fill up the next ones simply 
checking whether the i-1 or j-1 is
greater. 
3. the answer is in ans[rows-1][cols-1]
       
*/

#include <bits/c++io.h>

int square[4][4] = {
    {4, 3, 7},
    {9, 2, 5},
    {1, 2, 6},
};

int main(){
    int rows = 3, cols = 3;
    int ans[4][4];
    ans[0][0] = square[0][0];
    for (int i = 1; i != rows; i++ ){
        ans[i][0] = ans[i-1][0] + square[i][0];
    }
    for (int i = 1; i != cols; i++ ){
        ans[0][i] = ans[0][i-1] + square[0][i];
    }
    for (int i = 1; i != rows; i++ ){
        for (int j = 1; j != cols; j++){
            if (ans[i][j-1] + square[i][j] > ans[i-1][j] + square[i][j]){
                ans[i][j] = square[i][j] + ans[i-1][j];
            } else 
                ans[i][j] = square[i][j] + ans[i][j-1];
        }
    }
    
    printf("%d\n", ans[rows-1][cols-1]); 

    return 0;
}
        
