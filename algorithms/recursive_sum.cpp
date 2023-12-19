#include <cstdio>
#include <iostream>

int sum(int list[], int index){
    if (index == -1) return 0;
    return list[index] + sum(list, index-1);
}

int main() {
    int count;
    printf("input size of array: ");
    std::cin >> count;
    int list[count];
    for (int i=0; i != count; i++){
        printf("input the %d: ", i+1);
        std::cin >> list[i];
    }
    printf("SUM: %d\n", sum(list, count-1));

    return 0;
}
