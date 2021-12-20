// Find file size, check if size % 4 == 0
// Read first half of file, qsort it, write it to t1
// Read second hald of file, qsort it, write it to t2
// Manually merge one by one to t3
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>

int compar(const void* a, const void* b);
int createTemp(void);

int compar(const void* a, const void* b) {
    const uint32_t* ca = (const uint32_t*) a;
    const uint32_t* cb = (const uint32_t*) b;

    return *ca - *cb;
}

int createTemp(void) {
    int fd;
    char t[12];
    strncpy(t, "peshoXXXXXX", 12);
    
    if((fd = mkstemp(t)) == -1) {
        err(7, "temp");
    }
    return fd;
}

int main(int argc, char** argv) {

    int fd;
    int ecount;
    struct stat s;

    if(argc < 2) {
        errx(0, "input");
    }

    char* f = argv[1];

    if((fd = open(f, O_RDWR)) == -1) {
        err(1, "file");
    }

    if(fstat(fd, &s) == -1) {
        err(2, "stat");
    }

    if(s.st_size % 4 != 0) {
        errx(3, "file size");
    }

    ecount = s.st_size / 4;

    if(ecount > 100000000) {
        errx(4, "elements count");
    }

    int half = ecount / 2;
    int rest = ecount - half;

    uint32_t* fh = malloc(half*sizeof(uint32_t));
    
    if(fh == NULL) {
        err(5, "malloc"); 
    }

    for(int i = 0; i < half; ++i) {
        if(read(fd, &fh[i], sizeof(uint32_t)) != sizeof(uint32_t)) {
            err(6, "read");
        }
    }

    qsort(fh, half, sizeof(uint32_t), compar);

    int fdt1 = createTemp();

    for(int i = 0; i < half; ++i) {
        if(write(fdt1, &fh[i], sizeof(uint32_t)) != sizeof(uint32_t)) {
            err(7, "write");
        }
    }

    lseek(fdt1, 0, SEEK_SET);
    free(fh); 

    fh = malloc(rest*sizeof(uint32_t));

    if(fh == NULL) {
        err(8, "malloc");
    }
    
    for(int i = 0; i < rest; ++i) {
        if(read(fd, &fh[i], sizeof(uint32_t)) != sizeof(uint32_t)) {
            err(9, "read");
        }
    }

    int fdt2 = createTemp();

    qsort(fh, rest, sizeof(uint32_t), compar);

    for(int i = 0; i < rest; ++i) {
        if(write(fdt2, &fh[i], sizeof(uint32_t)) != sizeof(uint32_t)) {
            err(10, "write");
        }
    }

    free(fh);

    lseek(fdt2, 0, SEEK_SET);

    int out;
    if((out = open("out", O_WRONLY | O_TRUNC | O_CREAT, 
        S_IRUSR | S_IWUSR)) == -1) {
        err(11, "open");
    }

    uint32_t left;
    uint32_t right;

    while(read(fdt1, &left, sizeof(left)) == sizeof(left) &&
            read(fdt2, &right, sizeof(right)) == sizeof(right)) {

        if(left < right) {
            write(out, &left, sizeof(left));
            lseek(fdt2, -1*sizeof(right), SEEK_CUR);
        } else {
            write(out, &right, sizeof(right));
            lseek(fdt1, -1*sizeof(left), SEEK_CUR);
        }
    }

    while(read(fdt1, &left, sizeof(left)) == sizeof(left)) {
            write(out, &left, sizeof(left));
    }
    while (read(fdt2, &right, sizeof(right)) == sizeof(right)) {
            write(out, &right, sizeof(left));
    }

/*
    int h = 0;
    int r = 0;

    if (read(fdt1, &left, sizeof(left)) == sizeof(left)) {
        h++;
    }
    if (read(fdt2, &right, sizeof(right)) == sizeof(right)){
        r++;
    }

    while (h <= half && r <= rest) {
        if(left < right) {
            write(out, &left, sizeof(left));
            if (read(fdt1, &left, sizeof(left)) == sizeof(left)) {
            }
            h++;
        } else {
            write(out, &right, sizeof(right));
            if (read(fdt2, &right, sizeof(right)) == sizeof(right)){
            }
            r++;
        }
    }
    printf("foo\n");
    while (h <= half) {
            write(out, &left, sizeof(left));
            if (read(fdt1, &left, sizeof(left)) == sizeof(left)) {
                h++;
            } else {
                break;
            }
    }
    while (r <= rest) {
            write(out, &right, sizeof(left));
            if (read(fdt2, &right, sizeof(right)) == sizeof(right)) {
                r++;
            } else {
                break;
            }
    }
*/

    close(fd);
    close(fdt1);
    close(fdt2);
}





