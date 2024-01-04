#include <bits/stdc++.h>
#include <vector>

typedef std::vector<int> vi;
typedef std::vector<vi>  vv;


void gen_subset(vi set, vv *res, vi sub, int index){
    res->push_back(sub);
    for (int i = index; i != set.size(); i++){
        sub.push_back(set.at(i));
        gen_subset(set, res, sub, i+1);
        sub.pop_back();
    }
}

vv subset(vi set){
    vv res;
    vi sub;
    gen_subset(set, &res, sub, 0);
    return res;
}


int main(){
    vi set = {0, 1, 2};
    vv sub = subset(set);
    for (auto& s: sub){
        printf("{");
        for (auto& i: s)
            printf(" %d ", i);
        printf("}\n");
    }
    printf("\n");

}
