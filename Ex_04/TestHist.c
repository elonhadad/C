#include "Hist.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


static Element clone_int(Element int_elem) {
    int *p = malloc(sizeof(int));
    *p = *((int*)int_elem);
    return p;
}

static bool cmp_int(Element int_elem_1, Element int_elem_2) {
    return *((int*)int_elem_1) == *((int*)int_elem_2);
}

/* A function that checks the hist with integer elements */
static void test_int_hist1() {
    Hist hist = HistCreate(clone_int, free, cmp_int);
    assert(HistSize(hist) == 0);
    int i0=0, i1=1, i7=7;
    HistInc(hist, &i0);
    HistInc(hist, &i7);
    HistInc(hist, &i7);
    assert(HistSize(hist) == 3);
    assert(HistGetCount(hist, &i7) == 2);
    HistInc(hist, &i7);
    assert(HistSize(hist) == 4);
    assert(HistGetCount(hist, &i7) == 3);
    assert(HistGetCount(hist, &i1) == 0);
    assert(cmp_int(HistGetElement(hist, 0), &i0));
    assert(cmp_int(HistGetElement(hist, 1), &i7));
    HistDestroy(hist);
}

/* A function that checks the hist with integer elements */
static void test_int_hist2(int n) {
    Hist hist = HistCreate(clone_int, free, cmp_int);
    for(int i=0; i<n; i++) {
        HistInc(hist, &i);
    }
    assert(HistSize(hist) == n);
    HistDestroy(hist);
}

static Element clone_str(Element str_elem) {
    char *p = malloc(strlen(str_elem)+1);
    strcpy(p, str_elem);
    return p;
}

static bool cmp_str(Element str_elem_1, Element str_elem_2) {
    return !strcmp(str_elem_1, str_elem_2);
}

/* A function that checks the hist with string elements */
static void test_str_hist() {
    Hist hist = HistCreate(clone_str, free, cmp_int);
    assert(HistSize(hist) == 0);
    HistInc(hist, "");
    HistInc(hist, "abc");
    HistInc(hist, "abc");
    HistInc(hist, "def");
    assert(HistSize(hist) == 4);
    assert(HistGetCount(hist, "abc") == 2);
    assert(HistGetCount(hist, "def") == 1);
    assert(cmp_str(HistGetElement(hist, 0), ""));
    HistInc(hist, "test");
    HistInc(hist, "test");
    HistInc(hist, "test");
    HistInc(hist, "test");
    HistInc(hist, "test");
    assert(HistGetCount(hist, "test") == 5);
    HistDestroy(hist);
}

void test_hist() {
    test_int_hist1();
    test_int_hist2(1100);
    test_str_hist();
}

