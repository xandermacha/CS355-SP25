#include <unistd.h>   // aka UNIX Standard; POSIX (Portable OS Interface) API incl read/write
#include <fcntl.h>    // aka File Control; POSIX API for open/close
#include <stdio.h>
#include <time.h>

struct login {
	char user_name[100];
	time_t time_stamp;
	char user_terminal[100];
};

#define LOGIN_FILE "login_file.txt"
// TODO: lab3
int main() {

	struct login currentLogin;		// login struct
	int iLoginFile;
	int iLoginLen=sizeof(currentLogin);

	iLoginFile=creat(LOGIN_FILE, S_IRUSR | S_IWUSR);
	if(iLoginFile==-1) {
		perror(LOGIN_FILE);
		return 1;
	}

	for(int i=0; i<3; i++) {
		sprintf(currentLogin.user_name, "user_%d", i); // writes formatted output to current login struct
		sprintf(currentLogin.user_terminal, "terminal_%d", i+10);	// adds terminal into info to file by incrementing user%d by 10 to get terminal num
		time(&currentLogin.time_stamp);
		write(iLoginFile, &currentLogin, iLoginLen);
		sleep(1);
	}
	close(iLoginFile);

	if((iLoginFile=open(LOGIN_FILE, O_RDONLY)) == -1) {
		perror(LOGIN_FILE);
		return 1;
	}
	while(read(iLoginFile, &currentLogin, iLoginLen)==iLoginLen) {
		printf("%s last logged in on terminal %s at %.24s\n", currentLogin.user_name, currentLogin.user_terminal, asctime(localtime(&currentLogin.time_stamp)));
	}
	close(iLoginFile);

	return 0;
}
