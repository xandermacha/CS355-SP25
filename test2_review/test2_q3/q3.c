#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int main(int ac, char *av[]) {
    // Check for proper command-line arguments.
    if (ac != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", av[0]);
        return -1;
    }

    // Retrieve file status information using stat.
    struct stat fileStat;
    if (stat(av[1], &fileStat) == -1) {
        perror(av[1]);
        return -1;
    }

    // Print the file size, inode number, and last access time.
    printf("File: %s\n", av[1]);
    printf("File size: %ld bytes\n", fileStat.st_size);
    printf("Inode number: %ld\n", fileStat.st_ino);
    printf("Last access time: %s", ctime(&fileStat.st_atime));  // ctime() includes a newline

    return 0;
}
