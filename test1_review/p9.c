/*
Problem 9. Write a complete C program called newfile that creates a file and populates 
it with data as follows. 
The first command line parameter is used as the file name to be created. 
All subsequent parameters are used as the content of the file. 
For example:
newfile Hello, have a nice day!
This will create a new file named Hello, 
whose content will be the following single line of text
have a nice day!
Provide the necessary logic for checking all reasonable error conditions. 
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main(int ac, char *av[]) {
	if(ac <= 2) {
		printf("usage %s filename text\n", av[1]);
		return 1;
	}
	int dst;
	int iNumBytes;
	dst = creat(av[1], S_IRUSR | S_IWUSR);

	if(dst<0) {
		perror(av[1]);
		return 1;
	}
	for(int i = 2; i<ac; i++) {
		if(write(dst, av[i], strlen(av[i])) == -1) {
			perror("write error");
			close(dst);
			return 1;
		}
		
		if(write(dst, " ", 1) == -1) {
			perror("write error");
			close(dst);
			return 1;
		}
	}

	if(write(dst, "\n", 1) == -1) {
		perror("write error");
		close(dst);
		return 1;
	}
	if(close(dst) == -1)
		perror("file close error");

	return 0;
}
