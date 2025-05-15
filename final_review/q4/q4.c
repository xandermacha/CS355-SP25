#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	int fd;
	if((fd = open("test.txt", O_RDONLY)) < 0){
		perror("error opening file");
		return 1;
	}
	printf("opened file");

	if(close(fd) < 0) {
		perror("error closing file");
		return 1;
	}
	printf("closed file");
	return 0;
}