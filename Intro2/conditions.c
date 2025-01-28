#include <stdio.h>

int main() {
    int iAge = 0;
    printf("How old are you?: ");
    int iReturnValue = scanf("%d", &iAge);

    if(iAge>=0 && iAge<=117){
        if(iAge<21) {
            printf("you cannot drink alcohol\n");
        }
        else {
            printf("hello your age is %d\n" ,iAge);
        }
    }
    else {
        printf("you entered invalid age: %d\n", iAge);
    }
    return 0;
}
