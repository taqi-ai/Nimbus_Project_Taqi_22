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
// --------------------------------------------------
// SORT: Compare names alphabetically (A → Z)
// --------------------------------------------------
static int cmp_name(const void *a, const void *b) {
    const Employee ea = (const Employee)a;
    const Employee eb = (const Employee)b;
    return strcmp(ea->name, eb->name);
}

// --------------------------------------------------
// SORT: Employees alphabetically by name
// --------------------------------------------------
void sort_employees_by_name(EmployeeArray *emps) {
    qsort(emps->data, emps->size, sizeof(Employee), cmp_name);
}

// --------------------------------------------------
// SORT: Compare KPI by ORS (high → low)
// --------------------------------------------------
static int cmp_kpi_score(const void *a, const void *b) {
    const KPI ka = (const KPI)a;
    const KPI kb = (const KPI)b;
    if (ka->ors < kb->ors) return 1;
    if (ka->ors > kb->ors) return -1;
    return 0;
}

// --------------------------------------------------
// SORT KPI results by overall rank score (ORS)
// Highest score first
// --------------------------------------------------
void sort_kpis_by_score(KPI *k, size_t n) {
    qsort(k, n, sizeof(KPI), cmp_kpi_score);
}