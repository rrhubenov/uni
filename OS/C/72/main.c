#include <stdint.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


struct package {
    char name[8];
    uint32_t offset;
    uint32_t length;
};

int main(int argc, char** argv) {

    if(argc != 2) {
        errx(2, "Arg count");        
    }

    int fd;
    struct stat s;

    struct package ps[8];

    if((fd = open(argv[1], O_RDONLY)) == -1) {
        err(3, "open");
    }

    if(fstat(fd, &s) == -1) {
        err(4, "stat");
    }

    if(s.st_size % sizeof(ps[0]) != 0) {
        errx(5, "file size is not divisible by package size");
    }

    int ecount = s.st_size / sizeof(ps[0]);

    if(ecount > 8) {
        errx(6, "more than 8 packages");
    }
    int count = 0;
    while(read(fd, &ps[count], sizeof(ps[count])) == sizeof(ps[count])) {
        count++;
    }

    int pids[8];
    int fds[2];

    if(pipe(fds) == -1) {
        err(10, "pipe");
    }

    for(int i = 0; i < ecount; ++i) {
       int pid = fork(); 

       if(pid == 0) {
           int cfd;
           if((cfd = open(ps[i].name, O_RDONLY)) == -1) {
                printf("%s\n", ps[i].name);
                err(7, "child open");
           }

           uint16_t result = 0;
           uint16_t buffer;
           //size of file has to be even
           if(lseek(cfd, ps[i].offset, SEEK_SET) == -1) {
                err(20, "lseek for child");
           }
           int read_bytes = 0;
           while(read(cfd, &buffer, sizeof(buffer)) == sizeof(buffer)) {
               read_bytes++;
               result = result ^ buffer;
               if((read_bytes/sizeof(uint16_t)) == ps[i].length) {
                 break;
               }
           }

           close(fds[0]);
           write(fds[1], &result, sizeof(result));

           close(cfd);
           close(fds[1]);
           exit(0);
       } else {
           pids[i] = pid;
       }
    }

    close(fds[1]);
    uint16_t presult = 0;
    int wstatus;

    for(int i = 0; i < ecount; ++i) {
        waitpid(pids[i], &wstatus, 1);
    }

    for(int i = 0; i < ecount; ++i) {
        uint16_t cresult;
        if(read(fds[0], &cresult, sizeof(cresult)) == -1) {
            err(12, "read from pipe");
        }
        presult = presult ^ cresult;
    }
    close(fds[0]);

    close(fd);

    printf("%uB\n", presult);

    return 0;
}
