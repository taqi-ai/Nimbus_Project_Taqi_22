#include <string.h>
#include <stdlib.h>
#include "sort_search.h"

// --------------------------------------------------
// SEARCH: Find employee index by ID
// Returns: index (0..n-1) or -1 if not found
// --------------------------------------------------
int find_employee_index_by_id(const EmployeeArray *emps, int id) {
    for (size_t i = 0; i < emps->size; i++) {
        if (emps->data[i].id == id)
            return (int)i;
    }
    return -1; // not found
}

// --------------------------------------------------
// FILTER: Get indexes of employees in a department
// Caller must free() the returned array
// --------------------------------------------------
int* filter_by_department(const EmployeeArray *emps,
                          const char *dept,
                          size_t *out_n)
{
    *out_n = 0;

    // First pass: count matches
    for (size_t i = 0; i < emps->size; i++) {
        if (strcmp(emps->data[i].department, dept) == 0)
            (*out_n)++;
    }

    if (*out_n == 0)
        return NULL;

    // Second pass: store indexes
    int *indexes = malloc((*out_n) * sizeof(int));
    size_t pos = 0;

    for (size_t i = 0; i < emps->size; i++) {
        if (strcmp(emps->data[i].department, dept) == 0)
            indexes[pos++] = (int)i;
    }

    return indexes;
}