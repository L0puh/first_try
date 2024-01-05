#include <bits/stdc++.h>
#include <vector>

typedef std::vector<int> vi;
typedef std::vector<vi> vv;
typedef std::vector<bool> vb;

void gen_perm(vv *res, vi sub, int index, int sz){
    if (index < sz){
        for (int i = index; i < sz; i++){
            std::swap(sub.at(index), sub.at(i));
            gen_perm(res, sub, index+1, sz);
            std::swap(sub.at(index), sub.at(i));
        }
    } else 
        res->push_back(sub);
}

vv permutations(vi array){
    vv res;
    gen_perm(&res, array, 0, array.size()); 
    return res;
}

int main(){
    vi array = {0, 1, 2 }; // 01 -> 01, 10  
    vv perms = permutations(array);
    for(auto& i: perms){
        for(auto& k: i){
            printf("%d ", k);
        }
        printf("\n");
    }

}
