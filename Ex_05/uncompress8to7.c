
#include <stdio.h>
#include <stdlib.h>

/*
Help function that gets two 8-bit numbers N and M,
and two indexes i≥0, j<8 and copies M to bits[i, j] in - N.
*/
unsigned char MinB(unsigned char N, unsigned char M, int i, int j){
    unsigned char mask = ~(((1 << (j-i+1))-1) << i);
    N &= mask;
    N &= ~(1<<7);
    M <<= i;
    N |= M;
    return N;
}

/* Function the un compress every 7bytes to 8bytes */
void unCompress8to7(char *input, char *output) {
    FILE *fp = fopen(input, "rb");
    if(fp == NULL) {
        fprintf(stderr, "%s %u: failed to open the file, aborting\n", __FILE__, __LINE__);
        exit(-1);
    }

    FILE *fOut = fopen(output, "w");
    if(fOut == NULL) {
        fprintf(stderr, "%s %u: failed to open the file, aborting\n", __FILE__, __LINE__);
        exit(-1);
    }

    int index = 0;
    int k;
    uint64_t fileSize = 0;
    int s = 0;

    /* checks the file size from the header report */
    while(1) {
        k = fgetc(fp);
        if(index > 7) {
            fileSize |= k<<s;
            s+=8;
        }

        index++;
        if(feof(fp)) {
            break;
        }
        if(index == 16) {
            break;
        }

    }
    fseek(fp, 0, SEEK_SET);

    int i = 0;
    int j = 0;

    int length = 0;

    while(1) {
        unsigned char a = fgetc(fp);
        j++;

        if(j >= 17) {
            if (j == 17) {
                unsigned char t = a & ~(1<<7);
                fputc(t, fOut);
                length += 1;
            }
            unsigned char b = fgetc(fp);
            if(b == 255) {
                b = ~b;
            }
            unsigned char d = MinB(b<<(i+1),a>>(7-i),0, i);    // Shift every two consecutive bytes
            if (b != 0){
                fputc(d, fOut);
                length += 1;
            }

            i++;
            if(feof(fp)) {
                break;
            }

            fseek(fp,-1, SEEK_CUR);
            if (i >= 7) {
                i=0;
                b &= ~(1<<7);
                fputc(b, fOut);
                length += 1;
            }
        }
    }

    /* Checks if the size of the files is equal */
    if(length != fileSize) {
        fprintf(stderr, "Mismatch between the file size reported in the header and the given file");
        exit(-1);
    }

    fclose(fp);
    fclose(fOut);
}

int main(int argc,char *argv[]) {
    // Checks if the number of arguments is correct
    if(argc != 3) {
        fprintf(stderr, "%s/%u: Two arguments expected, aborting\n", __FILE__, __LINE__);
        exit(-1);
    }
    unCompress8to7(argv[1],argv[2]);
    return 0;
}
