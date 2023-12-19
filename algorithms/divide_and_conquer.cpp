/* 
 
 finds the biggest 
 possible size
 of the given squre.
 divides the plot 
 evenly into squre plots.
 
 */


#include <cstdio>
#include <iostream>


struct Size{
    int x;
    int y;
};

void swap(int *x, int *y){
    int a = *x;
    *x = *y;
    *y = a;
}
Size square(int x, int y){
    if (y > x) swap(&x, &y);
    if (x % y != 0){
        int count = x / y;
        x = x-(count*y);
        return square(x, y);
    }
    else return {x/2, y};
}

int main(){
    int x, y;
    std::cin >> x >> y;

    Size res = square(x,y);
    std::printf("%dx%d\n", res.x, res.y);
    return 0;
}
