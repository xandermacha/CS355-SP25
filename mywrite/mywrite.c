#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFSIZE 1024

int main(int ac, char *av[]) {
	if(ac != 2) {
		fprintf(stderr, "usage %s ttyname\n", av[0]);
	}
	else {
		int fd = open(av[1], O_WRONLY);
		if(fd==-1) {
			perror("open failed");
		}
		else {
			char *hiMsg="message from other terminal...\n";
			char *byeMsg="bye\n";
			char buf[BUFFSIZE];
			write(fd, hiMsg, strlen(hiMsg));
			while(fgets(buf, BUFFSIZE, stdin) !=0 ) {
				write(fd, buf, strlen(buf));
			}
			write(fd, hiMsg, strlen(byeMsg));
			close(fd);
		}
	}
}
