// NOTE: demo of getopt() to parse input flags

#include <stdio.h>
#include <unistd.h>

// these flags are for mycat lab
int iflagE=0, iflagN=0, iflagS=0;

int main(int ac, char *av[]) {
	char option;
	while ((option = getopt(ac, av, "ens")) != -1) {
		switch(option) {
			case 'e':
				iflagE=1;
				printf("flag E enabled\n");
				break;
			case 'n':
				iflagN=1;
				printf("flag N enabled\n");
				break;
			case 's':
				iflagS=1;
				printf("flag S enabled\n"); 
				break;
		}
	}
	return 0;
}
