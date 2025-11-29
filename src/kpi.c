#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "kpi.h"
#include "stats.h"
#include "models.h"

static void minmax(const double *v, size_t n, double *mn, double *mx){
    *mn = 1e18;
    *mx = -1e18;
    for(size_t i=0; i<n; i++){
        if(v[i] < *mn) *mn = v[i];
        if(v[i] > *mx) *mx = v[i];
    }
    if(*mn == 1e18){ *mn = 0; *mx = 1; }
}

static double norm(double x, double mn, double mx){
    if(mx - mn < 1e-9) return 0.5;
    if(x < mn) x = mn;
    if(x > mx) x = mx;
    return (x - mn) / (mx - mn);
}

void compute_kpis(const EmployeeArray *emps,
                  const TaskLogArray *logs,
                  KPI **out,
                  size_t *out_n)
{
    size_t n = emps->size;
    KPI *k = calloc(n, sizeof(KPI));
    if(!k){ *out = NULL; *out_n = 0; return; }

    for(size_t i=0; i<n; i++)
        k[i].employee_id = emps->data[i].id;

    for(size_t j=0; j<logs->size; j++){
        TaskLog t = logs->data[j];
        size_t idx = n;
        for(size_t i=0; i<n; i++){
            if(emps->data[i].id == t.employee_id){
                idx = i; break;
            }
        }
        if(idx == n) continue;

        k[idx].tasks++;
        k[idx].hours_total += t.hours_spent;
        k[idx].avg_quality += t.quality_score;
        if(t.quality_score < 60) k[idx].errors++;
    }

    double *tphs = malloc(n * sizeof(double));
    double *avgqs = malloc(n * sizeof(double));

    for(size_t i=0; i<n; i++){
        if(k[i].tasks > 0)
            k[i].avg_quality /= k[i].tasks;

        k[i].error_rate_s = (k[i].errors + 1.0) / (k[i].tasks + 2.0);
        k[i].ri = 1.0 - k[i].error_rate_s;

        k[i].tph = (k[i].hours_total > 0) ?
                    (double)k[i].tasks / k[i].hours_total : 0.0;

        tphs[i] = k[i].tph;
        avgqs[i] = k[i].avg_quality / 100.0;
    }

    double mn_tph, mx_tph, mn_q, mx_q;
    minmax(tphs, n, &mn_tph, &mx_tph);
    minmax(avgqs, n, &mn_q, &mx_q);

    for(size_t i=0; i<n; i++){
        double ps = 0.5 * norm(k[i].tph, mn_tph, mx_tph)
                  + 0.5 * norm(avgqs[i], mn_q, mx_q);

        k[i].ps = ps;
        k[i].ors = 0.7 * ps + 0.3 * k[i].ri;

        if(ps < 0.4 || k[i].ri < 0.7) k[i].flag = "UNDER";
        else if(ps < 0.55 || k[i].ri < 0.8) k[i].flag = "WATCH";
        else k[i].flag = "OK";
    }

    free(tphs);
    free(avgqs);

    *out = k;
    *out_n = n;
}

const char* trend_for_employee(const TaskLogArray *logs,
                               int employee_id,
                               int N)
{
    if(N < 2) N = 2;

    double *q = malloc(N * sizeof(double));
    size_t count = 0;

    for(size_t j = logs->size; j > 0; j--){
        TaskLog t = logs->data[j-1];
        if(t.employee_id == employee_id){
            q[count++] = t.quality_score;
            if(count == (size_t)N) break;
        }
    }

    if(count < 2){
        free(q);
        return "Stable";
    }

    double s = slope(q, count);
    free(q);

    if(s > 0.5) return "Improving";
    if(s < -0.5) return "Worsening";
    return "Stable";
}