#ifndef MODELS_H
#define MODELS_H
#include <time.h>

#define NAME_MAX_LEN 64
#define DEPT_MAX_LEN 32
#define TASK_ID_MAX_LEN 32

typedef struct {
    int id;
    char name[NAME_MAX_LEN];
    char department[DEPT_MAX_LEN];
} Employee;

typedef struct {
    int employee_id;
    char task_id[TASK_ID_MAX_LEN];
    struct tm date;      
    double hours_spent;  
    double quality_score;
} TaskLog;

#endif