#include <stdint.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


double mean(uint32_t* values, int count);
double variance(uint32_t* values, int count);
uint64_t square(uint32_t a);

struct Session {
    uint32_t uuid;
    uint16_t _;
    uint16_t __;
    uint32_t start;
    uint32_t end;
};

uint64_t square(uint32_t a) {
    uint64_t b = (uint64_t) a;
    return b*b;
}

double mean(uint32_t* values, int count) {
    double sum = 0;
    for(int i = 0; i < count; ++i) {
        sum += values[i]; 
    }

    return ((double) sum) / ((double) count);
}

double variance(uint32_t* values, int count) {
    double m = mean(values, count);
    double sum = 0;

    for(int i = 0; i < count; ++i) {
        double term = values[i] - m;
        sum += term*term;
    }

    return ((double) sum) / ((double) count);
}

int main(int argc, char** argv) {

    int fd;
    struct Session sessions[16384];
    
    int count = 0;

    if(argc < 2) {
        errx(1, "input");
    }

    if((fd = open(argv[1], O_RDONLY)) == -1) {
        err(1, "opening file");
    }

    while(read(fd, &sessions[count], sizeof(sessions[0]))) {
        count++;
    }

    uint32_t* session_times = malloc(sizeof(uint32_t)*count);

    for(int i = 0; i < count; ++i) {
        session_times[i] = sessions[i].end - sessions[i].start;
    }

    double var = variance(session_times, count);

    struct Session matched_users[2048];
    short mucount = 0;

    for(int i = 0; i < count; ++i) {
        if(square(session_times[i]) > var) {
            matched_users[mucount] = sessions[i];
            mucount++;
        }
    }

    for(short i = 0; i < mucount; ++i) {
        struct Session curr = matched_users[i];
        uint32_t max = 0;
        for(int j = 0; j < count; ++j) {
            if(sessions[j].uuid == curr.uuid) {
                uint32_t session_time = sessions[j].end - sessions[j].start;
                if(session_time > max) {
                    max = session_time;
                }
            }
        }
        printf("%d %d\n", curr.uuid, max);
    }

    close(fd);
    free(session_times);

    return 0;
}













