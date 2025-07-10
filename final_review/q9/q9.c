#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/**
 * Exclude from `src` any character found in `exclude_chars`.
 * Returns a malloc’d string which the caller must free.
 */
char* exclude(const char* src, const char* exclude_chars) {
    bool table[256] = { false };

    // Mark all characters to be excluded
    for (const unsigned char *p = (const unsigned char*)exclude_chars; *p; ++p) {
        table[*p] = true;
    }
    int l = 0;
    while(src[l]) l++;

    // size_t len = strlen(src);
    char *out = malloc(l + 1);
    if (!out) return NULL;  // allocation failed

    char *dst = out;
    for (const unsigned char *p = (const unsigned char*)src; *p; ++p) {
        if (!table[*p]) {
            *dst++ = *p;
        }
    }
    *dst = '\0';
    return out;
}
// void exclude(char str1[], char str2[]) {
//     for(int i = 0; str1[i] != '\0'; i++) {
//         for(int j =0; str2[j] != '\0'; j++) {
//             if(str1[i] == str2[j]) {
//                 for(int k = i; str1[k] != '\0'; k++) {
//                     str1[k] = str1[k+1];
//                 }
//                 i--;
//                 break;
//             }
//         }
//     }
// }

int main(void) {
    const char *s    = "What a beautiful day!";
    const char *ex   = "a!fW";
    // char str1[] = "What a beautiful day!";
    // char str2[] = "a!f";
    // printf("%s\n", str1);
    // exclude(str1, str2);
    // printf("%s\n", str1);

    char *filtered   = exclude(s, ex);

    if (filtered) {
        printf("%s\n", filtered);  // prints: Wht beutiul dy
        free(filtered);
    }
    return 0;
}
