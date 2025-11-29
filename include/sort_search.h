#ifndef SORT_SEARCH_H
#define SORT_SEARCH_H

#include <stddef.h>
#include "kpi.h"
#include "models.h"

// ----------- SEARCH FUNCTIONS -----------

// Search employee by ID
int find_employee_index_by_id(const EmployeeArray *emps, int id);

// Filter employees by department
// Returns array of indexes, out_n = count
int* filter_by_department(const EmployeeArray *emps, 
                          const char *dept, 
                          size_t *out_n);

// ----------- SORT FUNCTIONS -----------

// Sort KPI array by ORS (highest → lowest)
void sort_kpis_by_score(KPI *k, size_t n);

// Sort employees alphabetically by name
void sort_employees_by_name(EmployeeArray *emps);

#endif