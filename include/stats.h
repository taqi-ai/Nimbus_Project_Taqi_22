// include/stats.h
#ifndef STATS_H
#define STATS_H

#include <stddef.h>

double mean(const double *a, size_t n);
double median(double *a, size_t n);        // median may sort array copy in caller
double slope(const double *y, size_t n);   // regression slope over indices 0..n-1

#endif
