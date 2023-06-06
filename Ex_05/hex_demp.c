/* Student1: Rotem Elimelech, ID: 313284606
 * Student2: Elon Hadad, ID: 034672139 */

#include <stdio.h>
#include <stdlib.h>

/*
Help function that gets two 8-bit numbers N and M,
and two indexes i≥0, j<8 and copies M to bits[i, j] in - N.
*/
unsigned short MinB(unsigned short N, unsigned short M, int i, int j) {
    unsigned short mask = ~(((1 << (j-i+1))-1) << i);
    N &= mask;
    M <<= i;
    N |= M;
    return N;
}

/* Function that prints a hexadecimal file to the standard out by little endian */
void hexdump(char *filename) {
    FILE *fp = fopen(filename, "rb");
    if(fp == NULL) {
        fprintf(stderr, "%s %u: failed to open the file, aborting\n", __FILE__, __LINE__);
        exit(-1);
    }

    int a;
    int b;

    int count = 0;
    int j = 0;
    int spaces = 0;

    while(1) {
        a = fgetc(fp);
        b = fgetc(fp);
        unsigned short c = 0;

        if(count == 0) {
            printf("%08x ",j);
        }

        c = a | c;
        if(b != -1 && a != -1) {
            printf("%04x", MinB(c, b, 8,15));
            j+=2;
        }
        count += 2;

        if(b == -1 && a != -1) {
            printf("%04x", a);
            j += 1;
        }
        if(feof(fp)) {
            break;
        }

        if(spaces%2 == 0 && count != 16) {
            printf(" ");
        }

        if(count == 16) {
            printf("\n");
            count = 0;
        }
    }
    printf("\n%08x",j);
    fclose(fp);
}

int main(int argc, char *argv[]) {
    // Checks if the number of arguments is correct
    if(argc != 2) {
        fprintf(stderr, "%s/%u: One argument expected, aborting\n", __FILE__, __LINE__);
        exit(-1);
    }
    hexdump(argv[1]);
    return 0;
}
