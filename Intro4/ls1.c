#include <stdio.h>
#include <dirent.h>

void do_ls(char *dir_name) {
    DIR *dir_ptr;
    struct dirent *dirent_ptr;

    dir_ptr = opendir(dir_name);
    if (dir_ptr == 0)
    {
        perror(dir_name);
    }
    else {
        while (dirent_ptr = readdir(dir_ptr) != 0) {
            printf("directory entry: %s \n", dirent_ptr -> d_name);
        }
        closedir(dir_ptr);
    }
    
}

int main() {

    do_ls(".");
    return 0;
}