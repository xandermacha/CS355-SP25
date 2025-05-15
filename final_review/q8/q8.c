#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <signal.h>

int line_max;
int col_max;
const char *msg = "Hello, World!";

void handle_sigint(int);

int main() {
    initscr();
    noecho();
    curs_set(FALSE);        
    nodelay(stdscr, TRUE);
    signal(SIGINT, handle_sigint);
    
    int row_max, col_max;
    getmaxyx(stdscr, row_max, col_max);

    int x = col_max /2;
    int y = row_max/2; 
    int direction = 1;

    while(1) {
        clear();
        mvprintw(y, x, "%s", msg);
        refresh();
        
        if(y <= 0) {
            direction = 1;
        }
        else if(y >= row_max -1) {
            direction = -1;
        }
        
        y += direction;
        usleep(1000000);
    }
    return 0;
}

void handle_sigint(int signum) {
    endwin();
    exit(0);
}
