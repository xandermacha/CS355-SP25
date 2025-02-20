#include <stdio.h>

int main(int ac, char *av[]) {
    int i, j, k;
    for(i = 1; i < ac; i++){
        char strClean_av[1000];
        int intClean_str_len = 0;
        char *strCurrent_str = av[i];
        
        char cCurrent_char;

        for(j=0; (cCurrent_char = strCurrent_str[j]) != 0; j++) {
            if((cCurrent_char >= 'a' && cCurrent_char <= 'z') || (cCurrent_char >= 'A' && cCurrent_char <= 'Z')) {
                // add char to array if it is a alphabetical letter
                strClean_av[intClean_str_len++] = cCurrent_char;              
            }
        }
        // print a new line and add another letter from word for each line to until j reaches the length of word
        for(j=1; j<=intClean_str_len; j++) {
            // print all the chars up to j on same line
            for(k=0; k<j; k++){
                printf("%c", strClean_av[k]);
            }
            printf("\n");
        }
    }
    return 0;
}