/*Problem 8. Implement function myfopen() in C. 
 This function takes a file name as the only parameter, attempts to open it for reading (use O_RDONLY), 
checks whether it was open correctly, prints an error message if there were errors, 
and then returns a file descriptor. */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int myfopen(char *sFile_name){
	int fd;
	fd = open(sFile_name, O_RDONLY);
	if(fd==-1){
		perror(sFile_name);
	}
	return fd;
}

int main(){

	int myfile = myfopen("p8.txt");

	return 0;
}
