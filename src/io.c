#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "io.h"

int parse_date(const char *s, struct tm *out){
    if(!s) return 0;
    // Expect YYYY-MM-DD
    if(strlen(s)!=10 || s[4]!='-' || s[7]!='-') return 0;
    char yy[5], mm[3], dd[3];
    memcpy(yy, s, 4); yy[4]='\0';
    memcpy(mm, s+5, 2); mm[2]='\0';
    memcpy(dd, s+8, 2); dd[2]='\0';
    memset(out, 0, sizeof *out);
    out->tm_year = atoi(yy) - 1900;
    out->tm_mon  = atoi(mm) - 1;
    out->tm_mday = atoi(dd);
    return 1;
}

int load_csv(const char *path, TaskLogArray *logs){
    FILE *f = fopen(path, "r");
    if(!f) return 0;
    char line[256];

    // try to skip header if present
    if(fgets(line, sizeof line, f)==NULL){ fclose(f); return 0; }

    while(fgets(line, sizeof line, f)){
        TaskLog t; char date[16], task_id[TASK_ID_MAX_LEN];
        int got = sscanf(line, "%d,%31[^,],%10[^,],%lf,%lf",
                         &t.employee_id, task_id, date, &t.hours_spent, &t.quality_score);
        if(got==5){
            strncpy(t.task_id, task_id, TASK_ID_MAX_LEN);
            t.task_id[TASK_ID_MAX_LEN-1] = '\0';
            parse_date(date, &t.date);
            log_array_push(logs, t);
        }
    }
    fclose(f);
    return 1;
}

// Placeholder: will print header only until KPI struct exists
int save_kpis_csv(const char *path, const KPI *k, size_t n){
    FILE *f = fopen(path, "w");
    if(!f) return 0;
    fprintf(f, "employee_id,tasks,errors,hours_total,avg_quality,error_rate_s,tph,ps,ri,ors,flag\n");
    // fill rows after KPI module is added
    fclose(f);
    return 1;
}