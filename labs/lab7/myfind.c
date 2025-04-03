#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void do_find(char *dir_name, char *filename);
void print_perms(int mode);


// this function is called for every encountered directory entry
void process_entry(char *dir_entry_name, char *filename, char *current_dir, int *directory_has_match) {
	struct stat info;
	char full_path[1024];
	snprintf(full_path, sizeof(full_path), "%s/%s", current_dir, dir_entry_name);

	if (stat(full_path, &info) == -1) {
		perror(full_path);
	}
	else {
		if (strstr(dir_entry_name, filename) != 0) {
			if (!*directory_has_match) {
				printf("%s\n", current_dir);
				*directory_has_match = 1;
			}

			if (!S_ISDIR(info.st_mode)) {
				printf("   %s (", dir_entry_name);
				printf("%04o/", info.st_mode & 0777); 
				print_perms(info.st_mode);
				printf(")\n");
			}

			if (S_ISDIR(info.st_mode) && strcmp(dir_entry_name, ".") != 0 && strcmp(dir_entry_name, "..") != 0) {
				do_find(full_path, filename); 
			}
		}
	}
}

// explore all entries of the given directory
void do_find(char *dir_name, char *filename) {
	DIR *dir_ptr;               // pointer to a directory structure
	struct dirent *dirent_ptr;  // pointer to the current directory entry
	int dir_match = 0;
	dir_ptr = opendir(dir_name);
	if (dir_ptr == 0) {      // opendir could fail
		perror(dir_name);
		return;                 // the directory does not exist
	}

	while ((dirent_ptr = readdir(dir_ptr)) != 0) {
		process_entry(dirent_ptr->d_name, filename, dir_name, &dir_match);
	}
	closedir(dir_ptr);
}

int main(int ac, char *av[]) {
	char *ptr_filename;
	char *ptr_dir_start = ".";

	if (ac < 2 || ac > 3) {
		fprintf(stderr, "usage: %s filename [startpath]\n", av[0]);
		return 1;
	}
	ptr_filename = av[1];
	if (ac == 3) {
		ptr_dir_start = av[2];
	}

	do_find(ptr_dir_start, ptr_filename);
	return 0;
}

void print_perms(int mode) {
	char str_permission[11];
	str_permission[0] = S_ISDIR(mode) ? 'd' : '-';
	const mode_t arr_bit_mask[9] = { S_IRUSR, S_IWUSR, S_IXUSR,
				S_IRGRP, S_IWGRP, S_IXGRP,
				S_IROTH, S_IWOTH, S_IXOTH };
	const char perm_char[9] = { 'r', 'w', 'x',
				'r', 'w', 'x',
				'r', 'w', 'x' };

	for(int i=0; i<9; i++) {
		str_permission[i+1] = (mode & arr_bit_mask[i]) ? perm_char[i] : '-';
	}
	str_permission[10] = '\0';
	printf("%s", str_permission);
}
