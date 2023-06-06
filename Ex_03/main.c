/* Student1: Rotem Elimelech, ID: 313284606
 * Student2: Elon Hadad, ID: 034672139 */

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

int my_strlen(const char* str) {
    /* A function that receives a string and returns its length */

    int cnt = 0;
    while(*str) {
        cnt++;
        str++;
    }
    return cnt;
}

char* my_strcat(char* dest, const char* src) {
    /* A function that connects a string */

    int i = 0;
    int j = 0;

    while (dest[i])
        i++;
    while (src[j] != '\0'){
        dest[i + j] = src[j];
        j++;
    }
    dest[i + j] = '\0';
    return dest;
}

bool starts_with(const char* s, const char* prefix) {
    /* A function that checks if a string is a prefix of a string */

    int prefixLength = my_strlen(prefix);
    for(int i = 0; i<prefixLength; i++) {
        if(s[i] != prefix[i]) {
            return false;
        }
    }
    return true;
}

int num_word(const char* str) {
    /* A function that returns the number of words in a string */

    int i = 0;
    int sum = 0;
    while(str[i] != '\0') {
        if(str[i] == '\n') {
            break;
        }
        if(str[i] == ' ' || str[i] == '\n' || str[i] == '\t') {
            sum++;
        }
        i++;
    }
    return sum;
}

char* get_chapter_file_name(const char* s, const char* prefix, const char* suffix) {
    /* A function that adds a suffix and prefix to a string and clears the white spaces */

    unsigned int size = my_strlen(s) + my_strlen(prefix) + my_strlen(suffix)+1;
    char* filename;
    filename = (char*) malloc(size);
    if(filename == NULL) {
        printf("(%s, %d): failed to allocate %lu bytes", \
            __FILE__, __LINE__, sizeof(int)*size);
        exit(1);
    }

    int i;
    for(i = 0; i < my_strlen(prefix); i++) {
        filename[i] = prefix[i];
    }

    for(int j = 0; j < my_strlen(s); j++) {
        if(isspace(s[j]) && !isspace(s[j+1]) && s[j+1] != '\0') {
            filename[i] = '-';
            i++;
        }
        if(!isspace(s[j])) {
            filename[i] = s[j];
            i++;
        }
    }
    *(filename+i) = '\0';
    filename = my_strcat(filename,suffix);

    return filename;
}

int main(int argc, const char* argv[]) {
    if(argc != 4) {
        fprintf(stderr, "\nUsage:  <file-name> <prefix> <suffix>\n");
        return 1;
    }

    FILE* fp = fopen(argv[1], "r");
    if(fp == NULL) {
        perror("Unable to open file!");
        exit(1);
    }

    char* buf = NULL;
    size_t bufsize = 0;

    char* filename = get_chapter_file_name("PREFACE", argv[2], argv[3]);
    FILE* fin = fopen(filename, "w");

    if(fin == NULL) {
        perror("Unable to open file!");
        exit(1);
    }

    int chars = 0,words = 0,lines = 0;
    int totalChars = 0, totalWords = 0, totalLines = 0;
    while(getline(&buf, &bufsize, fp) != EOF) {
        if(starts_with(buf, "CHAPTER")) {
            printf("%-30s: %d lines, %d words, %d characters\n", filename, lines, words, chars);
            totalLines += lines;
            totalWords += words;
            totalChars += chars;
            fclose(fin);
            free(filename);
            filename = get_chapter_file_name(buf, argv[2], argv[3]);
            fin = fopen(filename, "w");

            chars = 0;
            words = 0;
            lines = 0;
        }

        fprintf(fin, "%s", buf);
        lines += 1;
        words += num_word(buf);
        chars += my_strlen(buf);
    }
    totalWords += words;
    totalLines += lines;
    totalChars += chars;
    printf("%-30s: %d lines, %d words, %d characters\n", filename, lines, words, chars);
    printf("%-30s: %d lines, %d words, %d characters\n", "TOTAL", totalLines, totalWords, totalChars);
    fclose(fin);
    free(filename);
    fclose(fp);
    free(buf);
    return 0;
}
