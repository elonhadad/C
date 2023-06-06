/* Student1: Rotem Elimelech, ID: 313284606
 * Student2: Elon Hadad, ID: 034672139 */

#include <stdio.h>
#include <stdlib.h>


/* Function the compress every 8bytes to 7bytes */
void compress8to7(char *input, char *output) {
    FILE *fp = fopen(input, "r");
    if(fp == NULL) {
        fprintf(stderr, "%s %u: failed to open the file, aborting\n", __FILE__, __LINE__);
        exit(-1);
    }

    FILE *fOut = fopen(output, "wb");
    if(fOut == NULL) {
        fprintf(stderr, "%s %u: failed to open the file, aborting\n", __FILE__, __LINE__);
        exit(-1);
    }

    /* Code that print the first line of the output file */
    uint64_t size, MAGIC = 0x0087008700870087ll;
    fwrite(&MAGIC, sizeof(size), 1, fOut);
    fseek(fp, 0, SEEK_END);
    size =  ftell(fp);
    fwrite(&size, sizeof(size), 1, fOut);

    fseek(fp, 0, SEEK_SET);
    int i = 0;

    while(1) {
        unsigned char a = fgetc(fp);
        unsigned char b = fgetc(fp);

        if(b == 255) {
            b = ~b;
        }

        if(a > 127 || b > 127) {
            fprintf(stderr, "%s/%u: Byte over 127bit, aborting\n", __FILE__, __LINE__);
            exit(-1);
        }

        unsigned char c = (a >> i) | (b << (7 - i));   // Shift every two consecutive bytes and write to output file
        fputc(c, fOut);
        i++;
        if(feof(fp)) {
            break;
        }
        fseek(fp, -1, SEEK_CUR);
        if (i >= 7) {
            i=0;
            fseek(fp, 1, SEEK_CUR);
        }
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
    compress8to7(argv[1], argv[2]);
    return 0;
}
