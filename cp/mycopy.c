#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFERSIZE 1024
int main(int ac, char *av) {
    int src, dst;
    src = open(av[1], O_RDONLY);
    dst = creat(av[2], S_IRUSR | S_IWUSR);

    char cBuffer[BUFFERSIZE];
    int iNumBytes;

    while((iNumBytes=read(src, cBuffer, BUFFERSIZE)>0)) {
        write(dst, cBuffer, iNumBytes);
    }
    close(src);
    close(dst);
    return 0;
}
