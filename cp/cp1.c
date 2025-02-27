/*
An implementation of a very basic verison of cp:
copy a source file into a destination file

Pseudocode:
    open sourcefile for reading
    open destinationfile for writing
    while not EOF
        read from sourcefile into buffer
        write from buffer into destinationfile
    close sourcefile
    close destinationfile
 */

 #include <stdio.h>
 #include <unistd.h>
 #include <fcntl.h>

 #define BUFFERSIZE 1024

 int main(int ac, char *av[]) {
    int src, dst;  // source and destination files
    char buffer[BUFFERSIZE];
    int numBytes;

    if(ac!=3) {    // this program must be used with exactly two parameters
        printf("Usage: %s source destination\n", av[0]);
        return 1;
    }

    src=open(av[1], O_RDONLY); // attempt to open the source file
    if(src<0) {
        perror(av[1]);
        return 1;
    }

    dst=creat(av[2], S_IRUSR | S_IWUSR); // attempt to open the destination file
    if(dst<0) {
        perror(av[2]);
        return 1;
    }

    int iteration = 1; 
    // i.e. until we reach the end of file
    while((numBytes=read(src,buffer,BUFFERSIZE))>0) {
        if(write(dst,buffer,numBytes)!=numBytes) {
            perror("Write error");
            return 1;
        }
        printf("Iteration %d, bytes read %d\n", iteration, numBytes);
        iteration++;
    }

    if(numBytes<0) {
        perror("Read error");
        return 1;
    }
    if(close(src)<0 || close(dst)<0) {
        perror("Error closing files");
        return 1;
    }
    return 0;
 }