/* *Problem 10. Write an implementation of function void triangle(int X, char C) that uses printf()
 * to generate a right triangle of size X filled with characters that are specified in parameter C.*/

#include <stdio.h>

void triangle(int X, char C) {
	for(int i = 0; i<X; i++) {
		for(int j = 0; j <= i; j++) {
			printf("%c", C);
		}
		printf("\n");
	}
}

int main() {
	triangle(5, '*');

	return 0;
}
