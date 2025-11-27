#include <stdlib.h>
#include <stdio.h>
#include "dynarray.h"

static void* xrealloc(void *p, size_t n) {
    void *q = realloc(p, n);
    if (!q) {
        perror("realloc");
        exit(1);
    }
    return q;
}

void emp_array_init(EmployeeArray *a) {
    a->data = NULL;
    a->size = 0;
    a->cap = 0;
}

void log_array_init(TaskLogArray *a) {
    a->data = NULL;
    a->size = 0;
    a->cap = 0;
}

void emp_array_push(EmployeeArray *a, Employee e) {
    if (a->size == a->cap) {
        a->cap = a->cap ? a->cap * 2 : 8;
        a->data = xrealloc(a->data, a->cap * sizeof *a->data);
    }
    a->data[a->size++] = e;
}

void log_array_push(TaskLogArray *a, TaskLog t) {
    if (a->size == a->cap) {
        a->cap = a->cap ? a->cap * 2 : 16;
        a->data = xrealloc(a->data, a->cap * sizeof *a->data);
    }
    a->data[a->size++] = t;
}

void emp_array_free(EmployeeArray *a) {
    free(a->data);
    a->data = NULL;
    a->size = a->cap = 0;
}

void log_array_free(TaskLogArray *a) {
    free(a->data);
    a->data = NULL;
    a->size = a->cap = 0;
}