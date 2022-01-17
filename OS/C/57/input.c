#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <err.h>
#include <unistd.h>

struct Session {
    uint32_t uuid;
    uint16_t _;
    uint16_t __;
    uint32_t start;
    uint32_t end;
};

int main() {
    int fd;
    if((fd = open("example", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR)) == -1){
        err(1, "opening");
    }

    struct Session s1 = { 32, 132,321,2000, 3000};
    struct Session s2 = { 33, 1321, 3213, 5000, 60000};
    struct Session s3 = { 32, 132,321,50000, 70000};
    struct Session s4 = { 33, 1321, 3213, 100000, 1000000};

    write(fd, &s1, sizeof(s1));    
    write(fd, &s2, sizeof(s2));    
    write(fd, &s3, sizeof(s3));    
    write(fd, &s4, sizeof(s4));    

    close(fd);
    
}
