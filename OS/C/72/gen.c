#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    int fd = open("test.txt", O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);

    char filename[8] = "child1\0\0";
    uint32_t offset = 0;
    uint32_t length = 2;

    char filename2[8] = "child2\0\0";
    uint32_t offset2 = 0;
    uint32_t length2 = 2;

    write(fd, &filename, sizeof(filename));
    write(fd, &offset, sizeof(offset));
    write(fd, &length, sizeof(length));

    write(fd, &filename2, sizeof(filename2));
    write(fd, &offset2, sizeof(offset2));
    write(fd, &length2, sizeof(length2));

    close(fd);
    return 0;

}
