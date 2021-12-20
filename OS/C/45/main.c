
// Program receives a name of a binary file which it sorts.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, char** argv) {

    char pair[2];
    char a;
    int fd;

    if(argc < 2) {
        printf("Program requires 1 positional argument\n");
        exit(EXIT_FAILURE);
    } 

    char* fileName = argv[1];

    if((fd = open(fileName, O_RDWR)) == -1) {
        write(2, "File failed to open in read/write mode\n",39); 
    }

    // bubble sort
    int filePointer = 0;
    while(read(fd, &a, 1)) {
        lseek(fd, filePointer, SEEK_SET);
        while(read(fd, &pair, 2)) {
            if(pair[0] > pair[1]) {
                lseek(fd, -2, SEEK_CUR);

                char temp = pair[0];
                pair[0] = pair[1];
                pair[1] = temp;
                
                write(fd, pair, 2);
            }
        }
        filePointer++;
        lseek(fd, filePointer, SEEK_SET);
    }

    close(fd);
    return 0;

}


size_t a[256];

for (char i=0; i<=255; i++) {
    a[i] = 0;
}

char c;
while (read(fd, &c, 1) == 1) {
        a[c]++;
}

lseek(fd, 0, SEEK_SET);

for (char i=0; i<=255; i++) {
        for (size_t j=a[i]; j>0; j--) {
            write(fdout, i, 1);
        }
}

