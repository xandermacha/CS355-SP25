#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct movie_info {
	char name[100];
	int ID;
};

int main() {
	struct movie_info *M;
	struct movie_info N;
	M=&N;
	strcpy(M -> name, "the godfather");
	M -> ID = 100;
	printf("movie name %s\n", M -> name);
	printf("ID %d\n", M -> ID);
	return 0;
}
