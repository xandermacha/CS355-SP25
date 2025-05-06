#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <unistd.h>


#define MIN_SPEED 1
#define MAX_SPEED 99

void ouch(int);     // forward delaration of a signal handler

char rand_char() {
    switch (rand() % 3) {
        case 0: return '0';
        case 1: return '1';
        case 2: return ' ';
    }
    return ' ';
}

int main(int ac, char *av[]) {
    long speed = 0;
    if (ac != 2) {
        fprintf(stderr, "usage: %s speed [1-99]\n", av[0]);
        return 1;
    }
    
    speed = atoi(av[1]);

    if (speed < MIN_SPEED || speed > MAX_SPEED) {
        fprintf(stderr, "speed must be between 1 and 99.\n");
        return 1;
    }
    initscr();              // initialize the curses library
    clear();                // clear the screen
    curs_set(0);            // hide the cursor
    noecho();

    signal(SIGINT, ouch);

    char matrix[COLS][LINES];

    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < LINES; j++) {
            matrix[i][j] = rand_char();
        }
    }

    while (true) {
        for (int i = 0; i < COLS; i++) {
            for (int j = LINES - 1; j > 0; j--) {
                matrix[i][j] = matrix[i][j - 1];
            }

            matrix[i][0] = rand_char();

            for (int k = 0; k < LINES; k++) {
                move(k, i); 
                addch(matrix[i][k]);
            }
        }

        refresh();

        usleep(1000000/speed);
    }

    endwin();

    return 0;
}

void ouch(int signum) {
    clear();
    endwin();

    signal(SIGINT, SIG_DFL);    // restore the default interrupt signal handler
    raise(SIGINT);              // generates an interrupt signal, which kills the process
}
