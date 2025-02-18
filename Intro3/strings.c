#include <stdio.h>
#include <string.h>

int main() {
    char *string1 = "Hello, World!"; //! not changable

    printf("string1: %s\n", string1);

    char string2[25] = "Hello, World!";

    printf("string2: %s\n", string2);
    // string2[5] = 'X';

    for(int i = 0; i <= strlen(string2); i++) {
        printf("string2[%d] = %c (%d)\n", i, string2[i], string2[i]);
    }


    return 0;
}