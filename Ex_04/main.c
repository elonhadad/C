
#include <stdio.h>
#include "Hist.h"
#include "LinkedList.h"
#include <stdlib.h>
#include <string.h>

#define SIZE 1024

Element clone_str(Element str_elem) {
    if (!str_elem) return NULL;
    char *p = malloc(strlen(str_elem)+1);
    if(!p) {
        fprintf(stderr, "%s/%u: failed to allocated %lu bytes, aborting\n", __FILE__, __LINE__, sizeof(double));
        exit(-1);
    }
    strcpy(p, str_elem);
    return p;
}

static bool cmp_str(Element str_elem_1, Element str_elem_2) {
    return !strcmp(str_elem_1, str_elem_2);
}

/* Help function for get text from the standard input */
void stdIn(Hist hist, LinkedList ll) {
    char input[SIZE];
    printf("Enter a text (ENTER TO STOP): \n");
    while(fgets(input,SIZE,stdin)!=NULL) {          // Receives text from the standard input
        if(strlen(input) == 1) {
            break;
        }
        HistInc(hist, input);                       // Add the lines to hist and linked list
        LLAdd(ll, LLSize(ll) ,input);
    }
}

/* Help function for print to the standard input */
void stdOut(Hist hist, LinkedList ll) {
    int length = (int) LLSize(ll);
    for(int i = 0; i < length; i++) {
        Element e = LLRemove(ll, 0);
        fprintf(stdout, "%3d %s", HistGetCount(hist, e), (char*)e);
    }
    exit(0);
}

/* Help function for read from input txt file */
void fileIn(char* filename, Hist hist, LinkedList ll) {
    char* buf = NULL;
    size_t bufsize = 0;

    FILE *fin = fopen(filename, "r");
    if (fin == NULL) {
        fprintf(stderr, "%s/%u: failed to open the file, aborting\n", __FILE__, __LINE__);
        exit(-1);
    }
    while(getline(&buf, &bufsize, fin) != EOF) {
        LLAdd(ll, LLSize(ll), buf);                 // Add the file lines to hist and linked list
        HistInc(hist, buf);
    }
    free(buf);
    fclose(fin);
}

/* Help function for print to output txt file */
void fileOut(char* filename, Hist hist, LinkedList ll) {
    FILE* fileout = fopen(filename, "w");
    if(fileout == NULL) {
        fprintf(stderr, "%s/%u: failed to open the file, aborting\n", __FILE__, __LINE__);
        exit(-1);
    }
    int length = (int) LLSize(ll);
    for(int i = 0; i < length; i++) {
        Element e = LLRemove(ll, 0);
        fprintf(fileout, "%3d %s", HistGetCount(hist, e), (char*)e);
    }
    fclose(fileout);
    exit(0);
}

int main(int argc, char* argv[]) {
    // Checks if the number of arguments is correct
    if(argc > 3) {
        fprintf(stderr, "%s/%u: Two arguments expected, aborting\n", __FILE__, __LINE__);
        exit(-1);
    }

    Hist hist = HistCreate(clone_str, free, cmp_str);
    LinkedList ll = LLCreate(clone_str, free);

    if(argc == 1) {
        stdIn(hist,ll);
        stdOut(hist, ll);
    }

    else if(argc == 2) {
        if(cmp_str(argv[1], "-") != 0) {
            stdIn(hist,ll);
            stdOut(hist, ll);
        } else {
            fileIn(argv[1], hist, ll);
            stdOut(hist, ll);
        }
    }

    else if(argc == 3) {
        if(cmp_str(argv[1], "-") != 0 && cmp_str(argv[2], "-") != 0) {
            stdIn(hist,ll);
            stdOut(hist, ll);
        }
        else if(cmp_str(argv[1], "-") == 0 && cmp_str(argv[2], "-") == 0) {
            fileIn(argv[1], hist, ll);
            fileOut(argv[2], hist, ll);
        }
        else if(cmp_str(argv[1], "-") == 0 && cmp_str(argv[2], "-") != 0) {
            fileIn(argv[1], hist, ll);
            stdOut(hist, ll);
        }
        else {
            stdIn(hist,ll);
            fileOut(argv[2], hist, ll);
        }
    }

    HistDestroy(hist);
    LLDestroy(ll);
    return 0;
}
