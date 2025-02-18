#include <stdio.h>
#include <string.h>
void strcpy1(char *dest, const char *src) {
    int i = 0;
    while (src[i] != 0)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = 0;
    
}
void strcpy2(char *dest, const char *src) {
    int i = 0;
    while (dest[i] = src[i] != 0)
    {
        i++;
    }
    // dest[i] = 0;
    
}
int main() { 
    char str1[100] = "Hello, World!";
    char str2[100];

    // strcpy(str2, str1);
    // printf("str2: %s\n", str2);

    strcpy2(str2, str1);
    printf("str2: %s\n", str2);

    return 0;
}