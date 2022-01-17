/*
    input.bin - uint16_t, little endian

    output.h - валиден C header файл.


    проверки:
        sizeof(input.bin <= 52488*2)


    output.h {
        #include <stdint.h>
        const uint32_t arrN = sizeof(input.bin / 2)
        const uint16_t* arr = { елементи от input.bin, delimiter ',' }
    }
*/

#include <err.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define SIZE 52488

int main(int argc, char** argv) {

    if(argc != 3) {
        errx(3, "invalid input count");
    }

    int fd;
    int outputfd;

    if((fd = open(argv[1], O_RDONLY)) == -1) {
        err(4, "open");
    }

    if((outputfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1) {
        err(5, "open output");
    }

    struct stat a;

    if(fstat(fd, &a) == -1) {
        err(6, "stat");
    }

    if((long unsigned int) a.st_size > SIZE*sizeof(uint16_t)) {
        errx(7, "input size");
    }
    if (((long unsigned int) a.st_size % sizeof(uint16_t) != 0)) {
        errx(7, "input size");
    }

    const char* LINE1 = "#include <stdint.h>\n";
    const char* LINE2 = "const uint16_t arr[] = {\n";
    const char* LINE3 = "};\n";
    const char* LINE4 = "const uint32_t arrN = %d;\n";

    dprintf(outputfd, LINE1);
    dprintf(outputfd, LINE2);

    uint16_t buffer;

    int r = 0;
    while((r = read(fd, &buffer, sizeof(buffer))) == sizeof(buffer)) {
        
        dprintf(outputfd, "0x%04x,\n", buffer);
    }
    if (r != 0) {
       err(1, "boo");
    }

    dprintf(outputfd, LINE3);
    dprintf(outputfd, LINE4, a.st_size/sizeof(uint16_t));

    close(fd);
    close(outputfd);

    return 0;
}
