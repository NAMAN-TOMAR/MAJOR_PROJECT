#include <math.h>
#include <string.h>
#include <stdio.h>
#include "stats.h"
#include "utils.h"

/* Calculate descriptive statistics; preserves logic from original */
Statistics calculate_descriptive_stats(Dataset *dataset) {
    Statistics stats;
    memset(&stats, 0, sizeof(Statistics));

    if (dataset->count == 0) return stats;

    double sum = 0, sum_sq = 0; // for variance later
    double sorted_data[MAX_DATA_POINTS];
    for (int i = 0; i < dataset->count; i++) {
        sorted_data[i] = dataset->data[i];
        sum += dataset->data[i];
    }

    sort_array(sorted_data, dataset->count);

    stats.mean = sum / dataset->count;
    stats.min = sorted_data[0];
    stats.max = sorted_data[dataset->count - 1];
    stats.range = stats.max - stats.min;

    int n = dataset->count;
    if (n % 2 == 0) stats.median = (sorted_data[n/2 - 1] + sorted_data[n/2]) / 2.0;
    else stats.median = sorted_data[n/2];

    /*
     * Quartiles — intentionally not using the “fancy” formulas.
     * Sometimes simple indexing is good enough, especially for teaching tools.
     */
    /* Simple quartile selection (not interpolation) to keep original behaviour */
    stats.q1 = sorted_data[n/4];
    stats.q2 = stats.median; // yeah this is redundant
    stats.q3 = sorted_data[(3*n)/4];
    stats.iqr = stats.q3 - stats.q1;
   // variance calc (sample version)
    for (int i = 0; i < dataset->count; i++) {
        sum_sq += pow(dataset->data[i] - stats.mean, 2);
    }
  /*
     * Could divide by n here for population variance, but sticking with n-1
     */  
  
  if (dataset->count > 1) stats.variance = sum_sq / (dataset->count - 1);
    else stats.variance = 0.0;
    stats.std_deviation = sqrt(stats.variance);

    return stats;
}

/* Pearson correlation; returns 0 if denominator is zero */
double calculate_correlation(double x[], double y[], int n) {
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0, sum_y2 = 0;
    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
        sum_y2 += y[i] * y[i];
    }
    double numerator = n * sum_xy - sum_x * sum_y;
    double denom = sqrt((n * sum_x2 - sum_x * sum_x) * (n * sum_y2 - sum_y * sum_y));
    return denom != 0 ? numerator / denom : 0.0;
}
/*
 * Pretty-printing the stats.
 * I added some extra spacing because I always like the clean look.
 */
void print_statistics(Statistics stats, const char *variable_name) {
    printf("\n========== DESCRIPTIVE STATISTICS ==========\n");
    printf("Variable: %s\n", variable_name);
    printf("─────────────────────────────────────────────\n");
    printf("Mean:                 %.4f\n", stats.mean);
    printf("Median:               %.4f\n", stats.median);
    printf("Standard Deviation:   %.4f\n", stats.std_deviation);
    printf("Variance:             %.4f\n", stats.variance);
    printf("Minimum:              %.4f\n", stats.min);
    printf("Maximum:              %.4f\n", stats.max);
    printf("Range:                %.4f\n", stats.range);
    printf("First Quartile (Q1):  %.4f\n", stats.q1);
    printf("Third Quartile (Q3):  %.4f\n", stats.q3);
    printf("Interquartile Range:  %.4f\n", stats.iqr);
    printf("═════════════════════════════════════════════\n");
}
