#include <stdio.h>
#include <stdlib.h>

unsigned short MinB(unsigned short N, unsigned short M, int i, int j) {
    unsigned short mask = ~(((1 << (j-i+1))-1) << i);
    N &= mask;
    M <<= i;
    N |= M;
    return N;
}

void hexdump(char *filename) {
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        fprintf(stderr, "%s %u: failed to open the file, aborting\n", __FILE__, __LINE__);
        exit(-1);
    }

    int a;
    int b;

    int count = 0;
    int j = 0;

    while(1) {
        a = fgetc(fp);
        b = fgetc(fp);
        unsigned short c = 0;

        if(count == 0) {
            printf("%07x ",j);
        }

        c = a | c;
        if(b != -1 && a != -1) {
            printf("%04x ", MinB(c, b, 8,15));
            j+=2;
        }
        if(b == -1 && a != -1) {
            printf("%04x ", a);
            j += 1;
        }
        count += 2;

        if(feof(fp)) {
            break ;
        }

        if(count == 16) {
            printf("\n");
            count = 0;
        }

    }
    printf("\n%07x ",j);
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "%s/%u: Two arguments expected, aborting\n", __FILE__, __LINE__);
        exit(-1);
    }
    hexdump(argv[1]);
    return 0;
}
