#include <stdio.h>

void swapC(char *dest, char *src, int n) {
	for(int i=0; i<n; i++) {
		*dest = *src;
		dest++;
		src++;
	}
}


int main() {
	char *src = "hello";
	char dest[10];
	printf("src: %s, dest: %s\n", src, dest);
	swapC(dest, src, 2);
	printf("src: %s, dest: %s\n", src, dest);
	return 0;
}

