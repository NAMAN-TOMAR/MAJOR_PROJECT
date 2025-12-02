#include <stdio.h>
#include "ml.h"
#include "io.h"
#include "stats.h"
#include "dataset.h"

/* Data normalization (z-score) example */
void data_normalization(void) {
    if (dataset_count == 0) { printf("\nNo datasets available!\n"); return; }
    
    printf("\n======== DATA NORMALIZATION ========\nSelect dataset to normalize:\n");
    
    for (int i=0;i<dataset_count;i++) printf("%d. %s\n", i+1, datasets[i].variable_name);
    int sel; scanf("%d",&sel); sel--;
    
    if (sel<0||sel>=dataset_count) { printf("Invalid selection!\n"); return; }
    Dataset *d = &datasets[sel];
    Statistics s = calculate_descriptive_stats(d);
    
    printf("\n======== NORMALIZED DATA (Z-score) ========\nOriginal -> Normalized\n----------------------------------------\n");
    
    for (int i=0;i<(d->count<20?d->count:20);i++){
        double z = (d->data[i] - s.mean) / (s.std_deviation ? s.std_deviation : 1.0);
        printf("%.2f -> %.4f\n", d->data[i], z);
    }
    if (d->count > 20) printf("... (%d more values)\n", d->count - 20);
    printf("\nNormalization Formula: Z = (X - Mean) / Std_Dev\n");
}

/* Outlier detection using IQR method */
void find_outliers(void) {
    if (dataset_count == 0) { printf("\nNo datasets available!\n"); return; }
    
    printf("\n======== OUTLIER DETECTION ========\nSelect dataset:\n");
    
    for (int i=0;i<dataset_count;i++) printf("%d. %s\n", i+1, datasets[i].variable_name);
    int sel; scanf("%d",&sel); sel--;
    
    if (sel<0||sel>=dataset_count) { printf("Invalid selection!\n"); return; }
    Dataset *d = &datasets[sel];
    Statistics s = calculate_descriptive_stats(d);
    double lower = s.q1 - 1.5 * s.iqr;
    double upper = s.q3 + 1.5 * s.iqr;
    printf("\nQ1: %.4f, Q3: %.4f, IQR: %.4f\nLower fence: %.4f, Upper fence: %.4f\n",
           s.q1, s.q3, s.iqr, lower, upper);
    int outliers = 0;
    
  
    for (int i=0;i<d->count;i++){
        if (d->data[i] < lower || d->data[i] > upper) {
            printf(" Value: %.2f (Position: %d)\n", d->data[i], i+1);
            outliers++;
        }
    }
    if (!outliers) printf(" No outliers found!\n");
    else printf("\nTotal outliers: %d out of %d values (%.1f%%)\n", outliers, d->count, outliers*100.0/d->count);
}

/* Simple data splitting by sequential split */
void data_splitting(void) {
    if (dataset_count == 0) { printf("\nNo datasets available!\n"); return; }
    
    printf("\n======== DATA SPLITTING (Train/Test) ========\nSelect dataset:\n");
    
    for (int i=0;i<dataset_count;i++) printf("%d. %s\n", i+1, datasets[i].variable_name);
    int sel; scanf("%d",&sel); sel--;
    
    if (sel<0||sel>=dataset_count) { printf("Invalid selection!\n"); return; }
    Dataset *d = &datasets[sel];
     
    printf("\nEnter train/test split percent (e.g., 70): ");
    int p; scanf("%d",&p);
    
    if (p <= 0 || p >= 100) { printf("Invalid percent!\n"); return; }
    int train = (d->count * p) / 100;
    int test = d->count - train;
    
     printf("\nTotal: %d, Train: %d (%.1f%%), Test: %d (%.1f%%)\n", d->count, train, p*1.0, test, 100.0-p);
    double sumt=0,sumtest=0;
    
    for (int i=0;i<train;i++) sumt += d->data[i];
    for (int i=train;i<d->count;i++) sumtest += d->data[i];
    
    if (train>0) printf("Train mean: %.2f\n", sumt / train);
    if (test>0) printf("Test mean: %.2f\n", sumtest / test);
}

/* Simple linear prediction using regression (same logic as original) */
void simple_prediction(void) {
    if (dataset_count < 2) { printf("\nNeed at least 2 datasets for prediction!\n"); return; }
    
    printf("\n======== SIMPLE PREDICTION MODEL ========\nAvailable datasets:\n");
    
    for (int i=0;i<dataset_count;i++) printf("%d. %s\n", i+1, datasets[i].variable_name);
    int xi, yi; printf("\nSelect input feature (X): "); scanf("%d",&xi);
    
    printf("Select target variable (Y): "); scanf("%d",&yi);
    xi--; yi--;
    
    if (xi<0||yi<0||xi>=dataset_count||yi>=dataset_count) { printf("Invalid selection!\n"); return; }
    int n = datasets[xi].count < datasets[yi].count ? datasets[xi].count : datasets[yi].count;
    double sumx=0,sumy=0,sumxy=0,sumx2=0;
    
    for (int i=0;i<n;i++){
        double xv = datasets[xi].data[i];
        double yv = datasets[yi].data[i];
        sumx += xv; sumy += yv; sumxy += xv*yv; sumx2 += xv*xv;
    }
    double slope = (n*sumxy - sumx*sumy) / (n*sumx2 - sumx*sumx);
    double intercept = (sumy - slope*sumx) / n;
    
    printf("\nModel: Y = %.4f + %.4f * X\n", intercept, slope);
    char cont = 'y';
    
  
    while (cont == 'y' || cont == 'Y') {
        printf("\nEnter value for %s: ", datasets[xi].variable_name);
        double xv; scanf("%lf",&xv);
        printf("Predicted %s: %.4f\n", datasets[yi].variable_name, intercept + slope * xv);
        printf("\nMake another prediction? (y/n): ");
        scanf(" %c", &cont);
    }
}
