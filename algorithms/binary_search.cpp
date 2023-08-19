#include <iostream>

int dic[] = {'a', 'b', 'c', 'd', 'e', 'm','o', 'q'};

int binary_search(char target, int size) {
    int low=0;
    int high = size;

    while(low <= high) {
       
        int mid = low + (high - low) / 2;
        
        if (target == dic[mid]) 
            return mid;

        if (dic[mid] > target) 
            high = mid - 1;          
        else 
            low = mid + 1;
    }

    return 0;
}
int binary_search(char target, int start, int end) {
    int mid = start + end / 2;

    if (dic[mid] == target) 
        return mid;

    if (dic[mid] > target) 
        return binary_search(target, start, mid-1);
    else
        return binary_search(target, mid+1, end);
}

int main () {
    std::cout << binary_search('c', 1, 7); 
    std::cout << binary_search('c', 7); 

    return 0;
}
