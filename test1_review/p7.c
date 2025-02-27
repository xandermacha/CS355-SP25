/*
 Problem 7. Write an implementation of function void printX(char* s) to print string s. 
 This function prints only digits and ignores (skips) all other characters.*/
#include <stdio.h>

void printX(char *s){
	
	while (*s!=0) {
		if(*s>=48 && *s<=57){
			printf("%c", *s);
		}
		s++;
	}
	printf("\n");
}

int main() {
	printX("po2o1p1lkasjdaj asdwq2121 797979 6969");
	
	return 0;
}
