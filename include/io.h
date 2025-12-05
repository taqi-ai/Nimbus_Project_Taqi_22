#ifndef IO_H
#define IO_H
#include <stddef.h>
#include <time.h>
#include "dynarray.h"

// Parse "YYYY-MM-DD" into struct tm; returns 1 on success, 0 on failure
int parse_date(const char *s, struct tm *out);

// Load logs CSV: employee_id,task_id,date,hours_spent,quality_score
int load_csv(const char *path, TaskLogArray *logs);

// Forward-declare KPI for later; save function will be filled after KPI is ready
typedef struct KPI KPI;
int save_kpis_csv(const char *path, const KPI *k, size_t n);

#endif
