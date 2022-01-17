#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <unistd.h>

/*

    cat 1 -> mkfifo 0

*/


int main(int argc, char** argv) {

    if(argc != 2) {
        errx(5, "input c");
    }

    int fifofd;

   // if((fifofd = mkfifo("pipe", S_IRWXU)) == -1) {
   //     err(1, "named pipe");
   // }

    int fds[2];

    if(pipe(fds) == -1) {
        err(2, "pipe");
    }
    
    if((fifofd = open("pipe", O_TRUNC)) == -1) {
        err(6, "opening named pipe");
    }

    int pid = fork();

    if(pid == -1) {
        err(3, "fork");
    }

    if(pid == 0) {
        //close(1);
        //dup(fifofd);
        execlp("cat", "cat", argv[1]);
    }


}
