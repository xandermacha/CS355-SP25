#include <stdio.h>
#include <dirent.h>

void do_ls(char *dir_name) {
	DIR *dir_ptr;
	struct dirent *dirent_ptr;	// pointer to a directory struct
	dir_ptr = opendir(dir_name);	// pointer to current directory entry
	// below is equal to
	// if(!dir_ptr)
	if(dir_ptr==0) {	// if opendir could fail
		perror(dir_name);	// if dir doesnt exist
	}
	else {
		while((dirent_ptr=readdir(dir_ptr)) != 0) {
			printf("directory entry: %s\n", dirent_ptr->d_name);
		}
		closedir(dir_ptr);
	} 
}
int main() {
	do_ls(".");
	return 0;
}
