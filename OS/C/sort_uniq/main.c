#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>

int main(const int argc, const char** argv) {

    if(argc != 2) {
        errx(1, "input");
    }
    
    int a[2];
    pipe(a);

    int pid = fork();

    if(pid == 0) {
        close(a[0]);
        dup2(a[1], 1);
        execlp("cat", "cat", argv[1], 0);
    }

    close(a[1]);

    int b[2];
    pipe(b);

    int sortpid = fork();

    if(sortpid == 0) {
        dup2(a[0], 0);
        close(b[0]);
        dup2(b[1], 1);
        execlp("sort", "sort", 0);
    }

    close(b[1]);

    dup2(b[0], 0);
    execlp("uniq", "uniq", "-c", 0);

}
