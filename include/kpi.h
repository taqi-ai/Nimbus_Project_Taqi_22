#ifndef KPI_H
#define KPI_H

#include <stddef.h>
#include "dynarray.h"

typedef struct KPI {
    int employee_id;
    int tasks;
    int errors;
    double hours_total;
    double avg_quality;
    double error_rate_s;
    double tph;
    double ps;
    double ri;
    double ors;
    const char *flag;
} KPI;

void compute_kpis(const EmployeeArray *emps,
                  const TaskLogArray *logs,
                  KPI **out,
                  size_t *out_n);

const char* trend_for_employee(const TaskLogArray *logs,
                               int employee_id,
                               int N);

#endif
