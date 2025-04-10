#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/ioctl.h>

#define FILEBUFFERSIZE 2048

void get_screen_dimensions(int *cols) {
    struct winsize wbuf;
    if (ioctl(0, TIOCGWINSZ, &wbuf) != -1) {
        *cols = wbuf.ws_col; 
    }
}

void print_files_in_columns(char *arr_ptr_file_names[], int intNum_files, int terminal_width) {
    int max_len = 0;
    for (int i = 0; i < intNum_files; i++) {
        int len = strlen(arr_ptr_file_names[i]);
        if (len > max_len) {
            max_len = len;
        }
    }
    int column_width = max_len + 3;

    int num_columns = terminal_width / column_width;
    if (num_columns < 1) {
        num_columns = 1;
    }

    for (int i = 0; i < intNum_files; i++) {
        printf("%-*s", column_width, arr_ptr_file_names[i]);
        if ((i + 1) % num_columns == 0) {
            printf("\n");
        }
    }
    if (intNum_files % num_columns != 0) {
        printf("\n");
    }
}

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
    if (optind >= 1 && (av[optind] != 0)) {
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


    int terminal_width = 80;
    get_screen_dimensions(&terminal_width);
    print_files_in_columns(arr_ptr_file_names, intNum_files, terminal_width);

    return 0;
}

