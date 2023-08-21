#include <iostream>

int data[] = {3, 5, 2, 3, 1, 9, 4, 10, 3};

void swap(int *a, int *b) {
    int c = *a; 
    *a = *b;
    *b = c;
}

int partition(int low, int high){ 
    int pivot = data[high];
    int i = low-1;
    for (int k=low; k < high; k++) {
        if (data[k] <= pivot) {
            i++;
            swap(&data[i], &data[k]);
        }
    }
    swap(&data[i+1], &data[high]);
    return i + 1;
}
int quick_sort(int low, int high) {

    if (low < high) {
        int pivot = partition(low, high); 
        quick_sort(pivot+1, high);
        quick_sort(low, pivot-1);
    }
    return 0;
}


int main () {
    int size = sizeof(data) / sizeof(data[0]);

    quick_sort(0, size-1);
    for (int i=0; i != size;  i++) {
        std::cout << data[i] << '\t'; 
    } 
}
