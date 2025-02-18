#include <stdio.h>

int product1(int, int); // prototype 
int product2(int, int); // prototype 
int product3(int, int*); // prototype 
int main() {
    int a,b;

    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b); // scans user ints and sets them to a and b
    printf("entered %d and %d\n", a, b);
    int itmp1 = product1(a, b);
    printf("product1: %d * %d = %d\n", a, b, itmp1);
    
    int itmp2 = product1(a, b);
    printf("product1: %d * %d = %d\n", a, b, itmp2);
    
    int itmp3 = product1(a, &b);
    printf("product1: %d * %d = %d\n", a, b, itmp3);
    return 0;
}

int product1(int x, int y) {
    return x*y;
}
int product2(int x, int y) {
    return x*y;
}
int product3(int x, int *y) {
    int result = x * (*y);
    x = 3;
    *y = 7;
    return result;
}