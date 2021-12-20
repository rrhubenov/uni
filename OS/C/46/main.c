#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdint.h>
#include<err.h>
#include<stdio.h>

int main(int argc, char** argv) {

    if(argc < 4) {
        write(2, "arguments\n", 11);
        errx(1, "err");
    }

    int fd1, fd2, fd3;
    char* file1 = argv[1];
    char* file2 = argv[2];
    char* file3 = argv[3];

    uint32_t interval[2];
    uint32_t file2Buffer;

    if((fd1 = open(file1, O_RDONLY)) == -1) {
        err(2, "file1");
    }

    if((fd2 = open(file2, O_RDONLY)) == -1) {
        /*
        const int old=errno;
        close(fd1);
        errno=old;
        */
        err(3, "file2");
    }

    if((fd3 = open(file3, O_WRONLY | O_CREAT | O_APPEND | O_TRUNC,
            S_IRUSR | S_IWUSR)) == -1) {
        err(4, "file3");
    }

    while(read(fd1, &interval, sizeof(interval)) == sizeof(interval)) {
        lseek(fd2, interval[0], SEEK_SET);
        for(uint32_t i = 0; i < interval[1]; ++i) {
            read(fd2, &file2Buffer, sizeof(file2Buffer));
            write(fd3, &file2Buffer, sizeof(file2Buffer));
        }
    }

    close(fd1);
    close(fd2);
    close(fd3);

}
