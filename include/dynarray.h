#ifndef DYNARRAY_H
#define DYNARRAY_H
#include <stddef.h>
#include "models.h"

typedef struct {
    Employee *data;
    size_t size, cap;
} EmployeeArray;


typedef struct {
    TaskLog *data;
    size_t size, cap;
} TaskLogArray;


void emp_array_init(EmployeeArray *a);
void emp_array_push(EmployeeArray *a, Employee e);
void emp_array_free(EmployeeArray *a);


void log_array_init(TaskLogArray *a);
void log_array_push(TaskLogArray *a, TaskLog t);
void log_array_free(TaskLogArray *a);


#endif
