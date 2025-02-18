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
    for(int i = 0; i<3; i++) {
        strcpy(currentLogin.user_name, "John");
        write(intLoginFile, &currentLogin, sizeof(struct login));
    }
    close(intLoginFile);    //syscall

    return 0;
}