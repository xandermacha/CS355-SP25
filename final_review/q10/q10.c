#include <stdio.h>
#include <unistd.h>   
#include <fcntl.h>   

int get_length(char str[]) {
    int  len = 0;
    for (int i = 0; str[i] !='\0'; i++){
        len++;
    }
    return len;
}


int main(int ac, char *av[]) {
    /* 1) require at least one argument */
    if (ac < 2) {
        printf("not enough args\n");
        return 1;
    }

    // int dst = open("output.txt", O_WRONLY);
    int dst = creat("output.txt", S_IRUSR | S_IWUSR);

    if (dst == -1) {
        perror("Couldn't open output.txt\n");
        return 1;
    }

    for (int i = 1; i < ac; ++i) {
        write(dst, av[i], get_length(av[i]));
        write(dst, "\n", 1);
    }

    close(dst);
    return 0;
}

