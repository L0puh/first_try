#include <iostream>
#include <vector>


int smallest(std::vector<int> unsorted){
    int min = unsorted[0], index = 0;
    for (int i =0; i != unsorted.size(); i++){
        if(unsorted.at(i) < min) {
            min = unsorted.at(i);
            index = i;
        }
    }
    return index;
}

void sort(std::vector<int> unsorted, std::vector<int> *sorted){
    int size = unsorted.size();
    for (int i =0; i != size; i++){
        int index = smallest(unsorted);
        sorted->push_back(unsorted.at(index));
        unsorted.erase(unsorted.begin()+index);
    }
}

int main() {
    std::vector<int> sorted;
    std::vector<int> unsorted= {33, 14,134, 234, 3241 ,23 , 3,43,2 ,34, 3,53,2, 134,34, 54,23, 234,32,4 ,34,3, 2,2 ,234 ,23, 34,\
    4,32, 234, 23};
    sort(unsorted, &sorted);

    for (auto& c: sorted){
        std::cout << c << "\n";
    }
    return 0;
}
