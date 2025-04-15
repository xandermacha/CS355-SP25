#include <fcntl.h>    // for open()
#include <unistd.h>   // for read() and close()
#include <stdio.h>    // for perror() and printf()
#include <stdlib.h>   // for exit() and EXIT_FAILURE

int main(int ac, char *av[]) {
    // Ensure exactly one command-line argument is passed.
    if (ac != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", av[0]);
	return -1;
    }

    // Open the file in read-only mode.
    int fd = open(av[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
	return -1;
    }

    // Create a character array of size 10 to hold the characters.
    char buffer[10];

    // Read up to 10 characters from the file.
    ssize_t bytesRead = read(fd, buffer, 10);
    if (bytesRead == -1) {
        perror("Error reading file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Print the characters read.
    // Using the precision field in the format specifier (%.*s) allows us
    // to print exactly the number of bytes read without requiring a null terminator.
	for(int i=0; i<bytesRead;i++) {
		putchar(buffer[i]);
	}
	printf("\n");
    // Close the file descriptor and check for errors.
    if (close(fd) == -1) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    return 0;
}
