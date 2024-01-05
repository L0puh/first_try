#include <bits/c++io.h>
#include <vector>

typedef std::vector<int> vi;

void merge(vi *v, vi left, vi right){
    int i=0, j=0, k=0;
    while (i < left.size() && j < right.size()){
        if (left[i] <= right[j]){
            v->at(k) = left[i];
            i++;
        } else {
            v->at(k) = right[j];
            j++;
        }
        k++;
    }
    while(i < left.size()){
        v->at(k) = left[i]; 
        i++;
        k++;
    }

    while(j < right.size()){
        v->at(k) = right[j]; 
        j++;
        k++;
    }
    
}

void sort(vi *v) {
    int sz = v->size();
    if (sz < 2) return;
    int mid = sz/2;
    vi left, right;
    left.insert(left.end(), v->begin(), v->begin()+mid);
    right.insert(right.end(), v->begin()+mid, v->end());
    sort(&left);
    sort(&right);
    merge(v, left, right);

}

void print_vector(vi v){
    for (auto& i: v){
        printf("%d ", i);
    }
    printf("\n");
}

int main(){
    vi v = {1, 3, 5, 7, 0, 9, 2, 4};
    sort(&v);
    print_vector(v);
}
