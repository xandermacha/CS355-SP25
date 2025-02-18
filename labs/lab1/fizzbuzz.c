#include <stdio.h>
#include <string.h>

void fizzCheck(int i) {
    int imod3 = i % 3;
    int imod5 = i % 5;
    if(imod3 != 0 && imod5 != 0) { // if i is not multiple of either 3 and 5
        printf("%2d", i);
    } 
    else {
        if(imod3 == 0){     // if multiple of 3 print fizz
            printf("Fizz");
        } 
        if(imod5 == 0) {    // if multiple of 5 print buzz
            printf("Buzz");
        }
    }
    printf("\n");   // newline for next print
}

int main() {
    int iFizz = 0;
    printf("Please enter an integer: ");
    scanf("%d", &iFizz);    // sets user input to iFizz
    
    if (iFizz > 0) {
        for (int i = 0; i <= iFizz; i++) {  // if user input is positive
            fizzCheck(i);
        }
    } else {
        for (int i = 0; i >= iFizz; i--) {  // if user input is negative
            fizzCheck(i);
        }
    }
    return 0;
}