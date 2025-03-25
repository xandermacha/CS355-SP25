
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

int iflagA=0, iflagR=0, iflagS=0;
void process_entry(char *dir_entry_name){
	printf("%s\n", dir_entry_name);
	struct stat info;
	if(stat(dir_entry_name, &info)==-1) {
		perror(dir_entry_name);
	}
	else {
		if(S_ISDIR(info.st_mode)) {
			printf("%s is a dir\n", dir_entry_name);
		}
		else {
			printf("Dir entry %s\n", dir_entry_name);
		}
	}
}
void ls_current_dir(char *dir_name) {
	DIR *dir_ptr;
	struct dirent *dirent_ptr;
	dir_ptr = opendir(dir_name);
	if(dir_ptr==0) {
		perror(dir_name);
	}
	else {
		while((dirent_ptr=readdir(dir_ptr)) != 0) {
			process_entry(dirent_ptr->d_name);
		}
		
	}
	
	
}
int main(int ac, char *av[]) {
	char option;
	while ((option = getopt(ac, av, "ars")) != -1) {
		switch(option) {
			case 'e':
				iflagA=1;
				break;
			case 'n':
				iflagR=1;
				break;
			case 's':
				iflagS=1;
				break;
		}
	}
	
	return 0;
}
