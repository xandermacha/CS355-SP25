#include <sys/stat.h>
#include <unistd.h>   // aka UNIX Standard; POSIX (Portable OS Interface) API incl read/write
#include <fcntl.h>    // aka File Control; POSIX API for open/close
#include <stdio.h>
#include <time.h>
#include <string.h>
/*
pseudocode to implement our very basic login records
    open loginfile
    repeat
        read loginfile record
        display loginfile record
    close loginfile
*/
struct login {
    char user_name[100];
    time_t time_stamp; 
};

#define LOGIN_FILE "login_file.txt"

int main() {
    struct login currentLogin;
    int intLoginFile;
    intLoginFile = creat(LOGIN_FILE, S_IRUSR | S_IWUSR); // syscall

    if(intLoginFile==-1){
        perror(LOGIN_FILE);
        return 1;
    }
    for(int i = 0; i<3; i++) {
        sprintf(currentLogin.user_name, "user_%d", i);
        time(&currentLogin.time_stamp);
        write(intLoginFile, &currentLogin, sizeof(struct login));
        sleep(1);
    }
    close(intLoginFile);    //syscall

    intLoginFile = open(LOGIN_FILE, O_RDONLY);
    for(int i = 0; i<3; i++) {
        read(intLoginFile, &currentLogin, sizeof(struct login));
        printf("User name #%d: %s logged in at %.24s\n", i, currentLogin.user_name, asctime(localtime(&currentLogin.time_stamp)));
    }
    close(intLoginFile);    //syscall

    return 0;
}