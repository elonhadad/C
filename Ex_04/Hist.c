#include "Hist.h"
#include "LinkedList.h"
#include "Set.h"
#include <stdio.h>
#include <stdlib.h>

#define    QUOTA        512

struct Hist {
    Element* array;
    size_t array_size;
    LinkedList ll;
    Set s;
    Element (*clone_func)(Element);
    void (*free_func)(Element);
    bool (*cmp_func)(Element, Element);
};

Hist HistCreate(Element (*clone_func)(Element), void (*free_func)(Element), bool (*cmp_func)(Element, Element)) {
    Hist hist = malloc(sizeof(struct Hist));
    if(!hist) {
        fprintf(stderr, "%s, %d: Failed to allocate memory\n", \
        __FILE__, __LINE__);
        exit(-1);
    }
    hist->array_size = QUOTA;
    hist->array = calloc(QUOTA, sizeof(Element));
    if(!hist->array) {
        fprintf(stderr, "%s/%u: failed to allocate %lu bytes\n\n",
                __FILE__, __LINE__, QUOTA*sizeof(Element));
        exit(-1);
    }
    hist->clone_func = clone_func;
    hist->free_func = free_func;
    hist->cmp_func = cmp_func;
    hist->ll = LLCreate(clone_func, free_func);
    hist->s = SetCreate(clone_func, free_func, cmp_func);
    return hist;
}

void HistDestroy(Hist hist) {
    LLDestroy(hist->ll);
    SetDestroy(hist->s);
    for(int i=0; i<hist->array_size; i++) {
        hist->free_func(hist->array[i]);
    }
    free(hist->array);
    free(hist);
}

unsigned int HistSize(Hist hist) {
    return LLSize(hist->ll);
}

int HistGetCount(Hist hist, Element e) {
    int count = 0;
    for(int i = 0; i<hist->array_size; i++) {
        if(hist->array[i] && hist->cmp_func(hist->array[i], e)) {
            count++;
        }
    }
    return count;
}

void HistInc(Hist hist, Element e) {
    int i;
    for(i=0; i<hist->array_size && hist->array[i]; i++);
    // If array is full we need to increase size
    if(i == hist->array_size) {
        hist->array_size *= 2;
        hist->array = realloc(hist->array, hist->array_size*sizeof(Element));
        if(!hist->array) {
            fprintf(stderr, "%s/%u: failed to re-allocated %lu bytes\n\n",
                    __FILE__, __LINE__, hist->array_size*sizeof(Element));
            exit(-1);
        }
        for(int j=i; j<hist->array_size; j++) {
            hist->array[j] = NULL;
        }

    }
    Element ee = hist->clone_func(e);
    hist->array[i] = ee;
    LLAdd(hist->ll, HistSize(hist), ee);
    if(!SetIsIn(hist->s, e)) {
        SetAdd(hist->s, ee);
    }
}

Element HistGetElement(Hist hist, unsigned int index) {
    if(index < 0 || index > HistSize(hist)-1) {
        return NULL;
    }
    Element e = hist->clone_func(LLRemove(hist->ll, index));
    LLAdd(hist->ll, index, e);
    return e;
}