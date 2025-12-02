#include <stdio.h>
#include "visualization.h"
#include "utils.h"
#include "stats.h"

/*
 * Quick-and-dirty ASCII histogram.
 * I’ve written fancier ones before but honestly,
 * this gets the job done and is easier to debug.
 */
void show_histogram(double arr[], int n) {
    if (n <= 0) { printf("Dataset empty.\n"); return; }

    printf("\n======== HISTOGRAM ========\n");

/*
     * Finding min/max manually instead of calling stats,
     * partly because  to remember how the stats module behaves
     */
    double min_val = data->data[0], max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
    }

    // 10 bins — arbitrary, but nice and round
    int bins = 10;
    int histogram[10] = {0}; // VLA okay in C99 but some compilers are picky
    double bin_width = (max_val - min_val) / bins;
   /*
     * If bin_width == 0, all values identical.
     * Using a fallback width of 1.0 just to avoid chaos.
     */
    if (bin_width == 0) bin_width = 1.0; /* avoid division by zero */

    for (int i = 0; i < n; i++) {
        int bin_index = (int)((arr[i] - min_val) / bin_width);
        if (bin_index >= bins) bin_index = bins - 1;
        if (bin_index < 0) bin_index = 0;
        histogram[bin_index]++;
    }

    for (int i = 0; i < bins; i++) {
        printf("%.2f-%.2f: ", min_val + i * bin_width, min_val + (i + 1) * bin_width);
        for (int j = 0; j < histogram[i]; j++) printf("*");
        printf(" (%d)\n", histogram[i]);
    }
}
