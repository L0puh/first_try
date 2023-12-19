#include <vector>
#include <cstdio>


std::vector<int> quick_sort(std::vector<int> list){
    if (list.size() < 2) return list;
    std::vector<int> greater;
    std::vector<int> smaller;

    int pivot = list[0];
    for (int i = 1; i != list.size(); i++)
    {
        if (list.at(i) > pivot)
            greater.push_back(list.at(i));
        else 
            smaller.push_back(list.at(i));
    }
    std::vector<int> s;
    if (!smaller.empty()){
        s = quick_sort(smaller);
    }
    s.push_back(pivot);
    if (!greater.empty()){
        std::vector<int> g = quick_sort(greater);
        s.insert(s.end(), g.begin(), g.end());
    }
    return s;
}

int main() {
    std::vector<int> nums = {3241, 23, 3, 43, 2, 34, 3, 53, 2, 134};
    nums = quick_sort(nums);
    for (const auto& i: nums){
        printf("%d\t", i);
    }
    printf("\n");
    return 0;
}
