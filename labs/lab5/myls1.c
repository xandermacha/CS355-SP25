#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#define FILEBUFFERSIZE 2048

int lexicographical(const void *element1, const void *element2) {
    const char *s1 = *(const char **)element1;
    const char *s2 = *(const char **)element2;
    return strcmp(s1, s2);
}
int reverse_lexicographical(const void *element1, const void * element2){
    const char *s1 = *(const char **)element1;
    const char *s2 = *(const char **)element2;
    return -strcmp(s1, s2);
}
int main(int ac, char *av[]) {
    int flagA = 0, flagR = 0, flagS = 0;
    char *ptr_dir_name = ".";
    char *arr_ptr_file_names[FILEBUFFERSIZE];
    char opt;
    int intNum_files = 0;
    while ((opt = getopt(ac, av, "ars")) != -1) {
        switch (opt) {
            case 'a':
                flagA = 1;
                break;
            case 'r':
                flagR = 1;
                break;
            case 's':
                flagS = 1;
                break;
            default:
                printf("%s usage: [-ars] [directory] \n", av[0]);
                return 1;
        }
    }
    if (optind >= 1 && (av[optind] != NULL)) {
        ptr_dir_name = av[optind];
        // printf("%s\n", ptr_dir_name);
    }
    
    // printf("%s\n", ptr_dir_name);
    DIR *dir_ptr = opendir(ptr_dir_name);
    if (dir_ptr == 0) {
        perror(ptr_dir_name);
        return 1;
    }
    struct dirent *dirent_ptr;
    while ((dirent_ptr = readdir(dir_ptr)) != 0 ) {
        char *ch_ptr_name = dirent_ptr -> d_name;
        
        if (!flagA && ch_ptr_name[0] == '.') {
            continue;
        }
        
        arr_ptr_file_names[intNum_files] = strdup(ch_ptr_name);
        
        intNum_files++;
    }
    closedir(dir_ptr);


    int (*compare_type)(const void*, const void*);

    if (flagS) {
        compare_type = lexicographical;
    } else if (flagR) {
        compare_type = reverse_lexicographical;
    }

    if (flagS || flagR) {
        qsort(arr_ptr_file_names, intNum_files, sizeof(char *), compare_type);
    }

    for (int i = 0; i < intNum_files; i++) {
        printf("%s\n", arr_ptr_file_names[i]);
        
    }
    
    return 0;
}


