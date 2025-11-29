#include <stdlib.h>
#include <math.h>
#include "stats.h"

double mean(const double *a, size_t n) {
    if (n == 0) return 0.0;
    double s = 0.0;
    for (size_t i = 0; i < n; i++) s += a[i];
    return s / (double)n;
}

static int cmpd(const void *x, const void *y) {
    double a = *(const double*)x;
    double b = *(const double*)y;
    return (a > b) - (a < b);
}

double median(double *a, size_t n) {
    if (n == 0) return 0.0;
    qsort(a, n, sizeof(double), cmpd);
    if (n & 1) return a[n/2];
    return (a[n/2 - 1] + a[n/2]) / 2.0;
}

double slope(const double *y, size_t n) {
    if (n < 2) return 0.0;
    double sx = 0.0, sy = 0.0, sxx = 0.0, sxy = 0.0;
    for (size_t i = 0; i < n; i++) {
        double xi = (double)i;
        sx  += xi;
        sy  += y[i];
        sxx += xi * xi;
        sxy += xi * y[i];
    }
    double den = n * sxx - sx * sx;
    if (fabs(den) < 1e-9) return 0.0;
    return (n * sxy - sx * sy) / den;
}

