#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    char buf[BUFSIZ];
    int  fd = open("myfile.txt", O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        perror("can't open");
        exit(1);
    }
    write(fd, "hey there how are you", 21);
    lseek(fd, 0, SEEK_SET);
    read(fd, buf, 4);
    lseek(fd, -4, SEEK_CUR);
    write(fd, "cleared all", 20);
    close(fd);
    return 0;
}