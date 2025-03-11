#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFERSIZE 1024
int iFlagE=0, iFlagN=0, iFlagS=0;

int open_file(char *);
void flagE_action();
void flagN_action(int *);

int main(int ac, char *av[]) {
	if(ac<3) {
		printf("%s [-ens] file1 [file2 ...]\n", av[0]);
		return 1;
	}
	char cOpt;
	char sBuff[BUFFERSIZE];
	int fd;
	int iNum_bytes_read;
	int boolLine_start = 1, boolLine_end = 0;
	int iteration = 1;
	while((cOpt = getopt(ac, av, "ens")) != -1) {
		switch(cOpt) {
			case 'e':
				iFlagE = 1;
				break;
			case 'n':
				iFlagN = 1;
				break;
			case 's':
				iFlagS = 1;
				break;
		}
	}
	if((fd = open_file(av[2])) == -1) {
		return fd;
	}
	int boolLine_empty = 1, boolLine_num_printed = 0;
	while((iNum_bytes_read=read(fd, &sBuff, BUFFERSIZE)) > 0) {
		for(int i = 0; i<iNum_bytes_read; i++) {
			char cCurrent = sBuff[i];
			if (cCurrent != '\n' && cCurrent != '\t' && cCurrent != ' ') {
				boolLine_empty = 0;
			}
			
			if(boolLine_start && (!boolLine_num_printed && iFlagN)) {
				flagN_action(&iteration);
				boolLine_num_printed = 1;
				iteration++;
			}
			if(cCurrent == '\n' && iFlagE) {
				boolLine_start = 1;
				boolLine_num_printed = 0;
				flagE_action();
			}
			else if(cCurrent == '\n') {
				boolLine_start = 1;
				boolLine_num_printed = 0;
			}

			if(boolLine_empty && iFlagS) {
				break;
			}
			putchar(cCurrent);
		}

	}
	/*printf("%s\n", av[2]);*/
	return 0;
}

void flagE_action() {
	putchar('$');
}
void flagN_action(int *iteration) {
	printf("%5d ", *iteration++);
}

int open_file(char *sFile_name) {
	int fd;
	if((fd = open(sFile_name, O_RDONLY)) == -1) {
		perror(sFile_name);
	}
	return fd;
}
