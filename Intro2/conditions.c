#include <stdio.h>

int main() {
    int iAge = 0;
    printf("How old are you?: ");
    scanf("%d", &iAge);

    if(iAge>=0 && iAge<=117){
        printf("hello your age is %d\n" ,iAge);
    }
    else 
    
    return 0;
}