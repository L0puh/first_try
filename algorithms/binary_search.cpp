#include <cstdio>
#include <iostream>
#include <string>
#include <valarray>
#include <vector>
#include "algo.h"

int bin_search(int target, std::vector<int> nums){
    int low = 0;
    int high = nums.size()-1;
    int mid;
    while (low <= high){
        mid = (low + high) / 2;
        if (nums[mid] < target) {
            low = mid+1;  
        } else if (nums[mid] > target){
            high = mid-1;
        } else if (nums[mid] == target){
            return mid;
        }
        printf("low:%d\nhigh:%d\nmid:%d\n\n", low, high, mid);
    }
    return mid;

}
int bin_search_recursive(int target, std::vector<int> nums, int high, int low){
    int mid = (high+low)/2;
    if (high <= low) return -1;
    if (nums.at(mid) == target) return mid;
    if (nums.at(mid) > target)
        return bin_search_recursive(target, nums, mid, low);
    else return bin_search_recursive(target, nums, high, mid);
}

int main () {
    int num = 0; 
    printf("enter a num[1-10]: ");
    std::cin >> num;
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int res = bin_search_recursive(num, nums, nums.size()-1, 0);
    printf("the %d element is in %d position\n", num, res);


    return 0;
}
