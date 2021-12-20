#include <unistd.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int compar(const void* a, const void* b) {
    //Couldn't cast directly to uint32_t, not 100% sure why.
    uint32_t* ca = (uint32_t*) a;
    uint32_t* cb = (uint32_t*) b;

    return *ca - *cb;
}

int main(int argc, char** argv) {

    int fd;
    uint32_t values[50 000 000];
    
    if(argc < 2) {
        errx(1, "input");
    }

    if((fd = open(argv[1], O_RDWR)) == -1) {
        err(2, argv[1]);
    }
       
    size_t bytesRead = read(fd, &values, sizeof(values));

    qsort(&values, bytesRead/4, sizeof(uint32_t), compar);
    lseek(fd, 0, SEEK_SET);
    write(fd, &values, bytesRead);
    size_t firstHalfEnd = bytesRead - 1;

    if((bytesRead = read(fd, &values, sizeof(values)))) {
        qsort(&values, bytesRead/4, sizeof(uint32_t), compar);
    }

    lseek(fd, firstHaldEnd, SEEK_SET);

    write(fd, &values, bytesRead);

    //Left half is sorted, write half is sorted. Best way to merge the
    //two halves?
    //First idea: read 25 mil uint32s from left half, read 25 mil 
    //uint32s from right half. Do the merge step manually and append the
    //resulting sorted merged array to the end of the file.
    //Repeat with the remaining uint32s.
    //When done delete the original values so that only the new appended data
    //remains.

    close(fd);

    return 0;
}
