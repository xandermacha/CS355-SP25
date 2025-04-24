#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <curses.h>

void ouch(int); // forward declaration of signal handler

int largest_prime = 2;
int sigint_received = 0;

int main() {
	signal(SIGINT, ouch); // ctrl + c

	initscr();
	noecho();

	int num = 2;

	while(1) {
		int is_prime = 1;
		for(int i = 2; i * i <= num; i++) {
			if(num % i == 0) {
				is_prime = 1;
				break;
			}
		}
		if(is_prime) {
			largest_prime = num;
		}
		num++;

		if(sigint_received) {
			sigint_received = 0;
			printw("%d\tQuit [y/n]? ", largest_prime);
			refresh();

			int ch = getch();

			printw("%c\n", ch);
			refresh();

			if(ch == 'y' || ch == 'Y') {
				break;
			}
		}
	}

	endwin();
	return 0;
}

void ouch(int signum) {
	sigint_received = 1;
}
