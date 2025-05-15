#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <signal.h>

#define UPEDGE 0
#define DOWNEDGE (LINES-1)
int line_max;
int col_max;
const char *msg = "Hello, World!";
int speed = 1000000;
void handle_sigint(int);

int main() {
    initscr();
    noecho();
    curs_set(FALSE);        
    nodelay(stdscr, TRUE);
    signal(SIGINT, handle_sigint);
    
    int row_max, col_max;
    getmaxyx(stdscr, row_max, col_max);

    int y = DOWNEDGE;
    int direction = 1;

    while(1) {
        clear();
        mvprintw(y, 0, "%s", msg);
        refresh();
        
        if(y <= UPEDGE) {
            direction = 1;
        }
        else if(y >= DOWNEDGE) {
            direction = -1;
        }
        
        y += direction;
        usleep(speed);
    }
    return 0;
}

void handle_sigint(int signum) {
    speed = speed/10;
}
