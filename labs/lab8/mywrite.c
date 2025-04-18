#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFSIZE 1024

int main(int ac, char *av[]) {
	char banned_words[5][10] = {"apple", "pear", "banana", "orange", "plum"};
	int ban_msg = 0;
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
			char *byeMsg="EOF\n";
			char buf[BUFFSIZE];
			write(fd, hiMsg, strlen(hiMsg));
			while(fgets(buf, BUFFSIZE, stdin) != 0 ) {
				ban_msg = 0;
				int i = 0;
				for(i = 0; i<5; i++){
					if(strstr(buf, banned_words[i]) != 0) {
						ban_msg = 1;
						break;
					}
				}
				if(ban_msg == 1) {
					printf("You enter prohibited word: %s. Message will not be sent.\n", banned_words[i]);
				}
				else {
					if(write(fd, buf, strlen(buf)) == -1) {
						break;
					}
				}
			}
			write(fd, byeMsg, strlen(byeMsg));
			close(fd);
		}
	}
}
