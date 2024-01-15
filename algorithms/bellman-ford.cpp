#include <bits/stdc++.h>
#include <cmath>
#include <vector>

struct node{
   int from;
   int to;
   int weight;
};

std::vector<node> graph{
   {1, 2, 5},
   {1, 3, 3},
   {3, 4, 1},
   {4, 6, 2},
   {2, 4, 3},
   {2, 6, 2}
};
const int N = graph.size();

int main(){
   int start = 1;
   int distance[N];
   std::fill(distance, distance+N, INT_MAX);
   distance[start] = 0;
   node solution[N];
   for (int i = 1; i <= N; i++){
      for (auto n: graph){
         // distance is the minimum of d[n.to] vs d[n.from]+n.weight
          if (distance[n.to] > distance[n.from] + n.weight){
             solution[n.to] = n;
             distance[n.to] = distance[n.from] + n.weight;
          }

       }
   }
   printf("shortest path %d -> %d: %d \n", start, N, distance[graph[N-1].to]);
   for (auto& n: graph){
      printf("%d -> %d [%d] \n", n.from, n.to, distance[n.to]);
   }


}
