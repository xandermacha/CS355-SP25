#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFERSIZE 2048

void print_file(const char *file, int flag_e, int flag_n, int flag_s, int *iteration);

int main(int ac, char *av[]) {
    int flagE = 0, flagN = 0, flagS = 0;
    if (ac < 2) {
        printf("%s usage: [-ens] file1 [file2 ...]\n", av[0]);
        return 1;
    }
    int iteration = 1;
    char opt;
    while ((opt = getopt(ac, av, "ens")) != -1) {
        switch (opt) {
            case 'e':
                flagE = 1;
                break;
            case 'n':
                flagN = 1;
                break;
            case 's':
                flagS = 1;
                break;
            default:
                printf("%s usage: [-ens] file1 [file2 ...]\n", av[0]);
                return 1;
        }
    }

    if (optind >= ac) {
        printf("%s requires at least 1 input file\n", av[0]);
        return 1;
    }

    for (int i = optind; i < ac; i++) {
        print_file(av[i], flagE, flagN, flagS, &iteration);
    }
    return 0;
}

void print_file(const char *file, int flag_e, int flag_n, int flag_s, int *iteration) {
    int src = open(file, O_RDONLY);
    if (src < 0) {
        perror(file);
        return;
    }
    
    char buffer[BUFFERSIZE];
    int numBytes;
    
    int line_start = 1;
    int empty_line = 1;
    int printed_line_number = 0;

    while ((numBytes = read(src, buffer, BUFFERSIZE)) > 0) {
        for (int i = 0; i < numBytes; i++) {
            char c = buffer[i];

            if (c == '\r') {
                continue;
            }

            if (line_start) {
                empty_line = 1;
                printed_line_number = 0;
                line_start = 0;
            }

            if (c != '\n' && c != '\t' && c != ' ') {
                empty_line = 0;
            }

            if (c == '\n') {
                if (!(flag_s && empty_line)) {
                    if (!printed_line_number && flag_n) {
                        printf("%5d ", (*iteration)++);
                        printed_line_number = 1;
                    }
                    if (flag_e) {
                        putchar('$');
                    }
                    putchar('\n');
                    line_start = 1;
                }
            } else {
                if (!printed_line_number && flag_n) {
                    printf("%5d ", (*iteration)++);
                    printed_line_number = 1;
                }
                putchar(c);
            }
        }

    }
    printf("\n");
    close(src);
}

