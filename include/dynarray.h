#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <stddef.h>
#include "models.h"

/*
 * Dynamic array structure for storing Employee records.
 * Maintains pointer to data, current size, and allocated capacity.
 */
typedef struct {
    Employee *data;   // Pointer to array of Employee
    size_t size;      // Number of elements currently stored
    size_t cap;       // Total allocated capacity
} EmployeeArray;

/*
 * Dynamic array structure for storing TaskLog entries.
 */
typedef struct {
    TaskLog *data;    // Pointer to array of TaskLog
    size_t size;      // Number of elements currently stored
    size_t cap;       // Total allocated capacity
} TaskLogArray;

/* -------- EmployeeArray Functions -------- */

/*
 * Initializes an EmployeeArray with default capacity.
 * Must be called before any push operations.
 */
void emp_array_init(EmployeeArray *a);

/*
 * Adds a new Employee to the dynamic array.
 * Automatically resizes the array when needed.
 */
void emp_array_push(EmployeeArray *a, Employee e);

/*
 * Frees allocated memory and resets the array fields.
 */
void emp_array_free(EmployeeArray *a);


/* -------- TaskLogArray Functions -------- */

/*
 * Initializes a TaskLogArray with default capacity.
 */
void log_array_init(TaskLogArray *a);

/*
 * Appends a TaskLog entry to the array, resizing if necessary.
 */
void log_array_push(TaskLogArray *a, TaskLog t);

/*
 * Releases memory allocated for the TaskLogArray.
 */
void log_array_free(TaskLogArray *a);

#endif // DYNARRAY_H
