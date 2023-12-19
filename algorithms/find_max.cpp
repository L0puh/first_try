/*
finds the max element
using recursive
*/

#include <cstdio>


int max(int list[], int index)  {
    if (index == 1){
        // the best case
        if (list[index] > list[index-1])
            return list[index];
        else return list[index-1];
    } 
    // the recursive case
    int s = max(list, index-1);
    if (list[index] > s) return list[index];
    return s;
}
int main() {
    int list[3] = {99952, 4283, 531};
    printf("MAX: %d\n", max(list, 3-1));
    return 0;
}
