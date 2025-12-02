#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "dataset.h"
#include "io.h"
#include "utils.h"
#include "stats.h"

//Global dataset storage

Dataset datasets[MAX_VARIABLES];
int dataset_count = 0;

/* Menus and navigation */
void display_main_menu(void) {
    clear_screen();
    printf("=================== MAIN MENU ===================\n");
    printf("1. Data Input & Management\n");
    printf("2. Statistical Analysis\n");
    printf("3. Data Visualization\n");
    printf("4. Machine Learning Basics\n");
    printf("5. Export Results\n");
    printf("6. Exit\n");
    printf("================================================\n");
}
//Tried to keep this menu readable, though it’s a bit repetitive.


void data_input_menu(void) {
    int choice = 0;
    do {
        clear_screen();
        printf("\n============= DATA INPUT & MANAGEMENT =============\n");
        printf("1. Manual Data Entry\n");
        printf("2. Load Data from File\n");
        printf("3. Generate Sample Data\n");
        printf("4. View Current Datasets\n");
        printf("5. Back to Main Menu\n");
        printf("=================================================\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) { while(getchar()!='\n'); choice = 0; }
        switch (choice) {
            case 1: manual_data_entry(); break;
            case 2: load_from_file(); break;
            case 3: generate_sample_data(); break;
            case 4: display_datasets(); break;
            case 5: break;
            default: printf("Invalid choice!\n");
        }
        if (choice != 5) { printf("\nPress Enter to continue..."); getchar(); getchar(); }
    } while (choice != 5);
}
//This one got a bit long — I might break it into submenus later

void statistical_analysis_menu(void) {
    int choice = 0;
    do {
        clear_screen();
        printf("\n============ STATISTICAL ANALYSIS ============\n");
        printf("1. Descriptive Statistics\n");
        printf("2. Correlation Analysis\n");
        printf("3. Linear Regression\n");
        printf("4. Hypothesis Testing\n");
        printf("5. Confidence Intervals\n");
        printf("6. Back to Main Menu\n");
        printf("==============================================\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) { while(getchar()!='\n'); choice = 0; }
        switch (choice) {
            case 1: {
                if (dataset_count == 0) { printf("\nNo datasets available!\n"); break; }
                printf("\nSelect dataset for analysis:\n");
                for (int i = 0; i < dataset_count; i++) printf("%d. %s\n", i+1, datasets[i].variable_name);
                int sel; scanf("%d", &sel);
                if (sel > 0 && sel <= dataset_count) {
                    Statistics s = calculate_descriptive_stats(&datasets[sel-1]);
                    print_statistics(s, datasets[sel-1].variable_name);
                } else printf("Invalid selection!\n");
                break;
            }
            case 2: {
                if (dataset_count < 2) { printf("\nNeed at least 2 datasets for correlation analysis!\n"); break; }
                printf("\nAvailable datasets:\n");
                for (int i = 0; i < dataset_count; i++) printf("%d. %s\n", i+1, datasets[i].variable_name);
                int a,b; printf("Select first dataset: "); scanf("%d",&a);
                printf("Select second dataset: "); scanf("%d",&b);
                a--; b--;
                if (a<0||b<0||a>=dataset_count||b>=dataset_count) { printf("Invalid selection!\n"); break; }
                int min_n = datasets[a].count < datasets[b].count ? datasets[a].count : datasets[b].count;
                double r = calculate_correlation(datasets[a].data, datasets[b].data, min_n);
                printf("\nVariables: %s vs %s\n", datasets[a].variable_name, datasets[b].variable_name);
                printf("Correlation coefficient (r): %.4f\n", r);
                printf("R-squared: %.4f\n", r*r);
                if (fabs(r) > 0.8) printf("Interpretation: Strong correlation\n");
                else if (fabs(r) > 0.5) printf("Interpretation: Moderate correlation\n");
                else printf("Interpretation: Weak correlation\n");
                break;
            }
            case 3: {
                /* This logic preserved from original: linear regression between two datasets */
                if (dataset_count < 2) { printf("\nNeed at least 2 datasets for regression analysis!\n"); break; }
                printf("\nAvailable datasets:\n");
                for (int i = 0; i < dataset_count; i++) printf("%d. %s\n", i+1, datasets[i].variable_name);
                int xi, yi; printf("\nSelect independent variable (X): "); scanf("%d",&xi);
                printf("Select dependent variable (Y): "); scanf("%d",&yi);
                xi--; yi--;
                if (xi<0||yi<0||xi>=dataset_count||yi>=dataset_count) { printf("Invalid selection!\n"); break; }
                int n = datasets[xi].count < datasets[yi].count ? datasets[xi].count : datasets[yi].count;
                double sumx=0,sumy=0,sumxy=0,sumx2=0;
                for (int i=0;i<n;i++){
                    double xv = datasets[xi].data[i];
                    double yv = datasets[yi].data[i];
                    sumx += xv; sumy += yv; sumxy += xv*yv; sumx2 += xv*xv;
                }
                double slope = (n*sumxy - sumx*sumy) / (n*sumx2 - sumx*sumx);
                double intercept = (sumy - slope*sumx) / n;
                double corr = calculate_correlation(datasets[xi].data, datasets[yi].data, n);
                printf("\nRegression Equation: Y = %.4f + %.4f * X\n", intercept, slope);
                printf("R-squared: %.4f\n", corr*corr);
                printf("\nEnter X value for prediction: ");
                double xpred; scanf("%lf",&xpred);
                printf("Predicted Y: %.4f\n", intercept + slope*xpred);
                break;
            }
            case 4: {
                /* Hypothesis testing preserved */
                if (dataset_count == 0) { printf("\nNo datasets available!\n"); break; }
                printf("\nSelect dataset for testing:\n");
                for (int i=0;i<dataset_count;i++) printf("%d. %s\n", i+1, datasets[i].variable_name);
                int sel; scanf("%d",&sel); sel--;
                if (sel<0||sel>=dataset_count) { printf("Invalid selection!\n"); break; }
                Dataset *d = &datasets[sel];
                Statistics s = calculate_descriptive_stats(d);
                printf("\nEnter hypothesized mean: "); double hyp; scanf("%lf",&hyp);
                double t_stat = (s.mean - hyp) / (s.std_deviation / sqrt(d->count));
                printf("\nSample Mean: %.4f\nHypothesized Mean: %.4f\nStd Dev: %.4f\nN: %d\nT-statistic: %.4f\n",
                       s.mean, hyp, s.std_deviation, d->count, t_stat);
                if (fabs(t_stat) > 2.0) printf("\nResult: The mean is SIGNIFICANTLY DIFFERENT from %.2f\n", hyp);
                else printf("\nResult: The mean is NOT significantly different from %.2f\n", hyp);
                break;
            }
            case 5: {
                /* Confidence intervals */
                if (dataset_count == 0) { printf("\nNo datasets available!\n"); break; }
                printf("\nSelect dataset for confidence interval:\n");
                for (int i=0;i<dataset_count;i++) printf("%d. %s\n", i+1, datasets[i].variable_name);
                int sel; scanf("%d",&sel); sel--;
                if (sel<0||sel>=dataset_count) { printf("Invalid selection!\n"); break; }
                Dataset *d = &datasets[sel];
                Statistics s = calculate_descriptive_stats(d);
                double me95 = 1.96 * (s.std_deviation / sqrt(d->count));
                double me99 = 2.576 * (s.std_deviation / sqrt(d->count));
                printf("\n95%% CI: [%.4f , %.4f]\n", s.mean - me95, s.mean + me95);
                printf("99%% CI: [%.4f , %.4f]\n", s.mean - me99, s.mean + me99);
                break;
            }
            case 6:
                break;
            default:
                printf("Invalid choice!\n");
        }
        if (choice != 6) { printf("\nPress Enter to continue..."); getchar(); getchar(); }
    } while (choice != 6);
}

void visualization_menu(void) {
    if (dataset_count == 0) { printf("\nNo datasets for visualization!\n"); return; }
    printf("\nSelect dataset to visualize:\n");
    for (int i=0;i<dataset_count;i++) printf("%d. %s\n", i+1, datasets[i].variable_name);
    int sel; scanf("%d",&sel); sel--;
    if (sel<0||sel>=dataset_count) { printf("Invalid selection!\n"); return; }
    show_histogram(&datasets[sel]);
}

void machine_learning_menu(void) {
    int choice = 0;
    do {
        clear_screen();
        printf("\n======== MACHINE LEARNING BASICS ========\n");
        printf("1. Data Normalization\n");
        printf("2. Find Outliers\n");
        printf("3. Data Splitting (Train/Test)\n");
        printf("4. Simple Prediction Model\n");
        printf("5. Back to Main Menu\n");
        printf("==========================================\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) { while(getchar()!='\n'); choice = 0; }
        switch (choice) {
            case 1: data_normalization(); break;
            case 2: find_outliers(); break;
            case 3: data_splitting(); break;
            case 4: simple_prediction(); break;
            case 5: break;
            default: printf("Invalid choice!\n");
        }
        if (choice != 5) { printf("\nPress Enter to continue..."); getchar(); getchar(); }
    } while (choice != 5);
}

void data_export_menu(void) {
    if (dataset_count == 0) { printf("\nNo data to export!\n"); return; }
    FILE *file = fopen("analysis_results.csv", "w");
    if (!file) { printf("Error creating export file!\n"); return; }
    fprintf(file, "Dataset,Mean,Median,Std_Dev,Min,Max\n");
    for (int i=0;i<dataset_count;i++){
        Statistics s = calculate_descriptive_stats(&datasets[i]);
        fprintf(file, "%s,%.4f,%.4f,%.4f,%.4f,%.4f\n",
                datasets[i].variable_name, s.mean, s.median, s.std_deviation, s.min, s.max);
    }
    fclose(file);
    printf("\nData exported to 'analysis_results.csv' successfully!\n");
}

/* Data input implementations */

void manual_data_entry(void) {
    if (dataset_count >= MAX_VARIABLES) { printf("\nMax datasets reached!\n"); return; }
    Dataset *cur = &datasets[dataset_count];
    printf("\nEnter variable name: ");
    scanf("%s", cur->variable_name);
    printf("How many data points? (max %d): ", MAX_DATA_POINTS);
    scanf("%d", &cur->count);
    if (cur->count > MAX_DATA_POINTS) { printf("Too many points! Setting to max.\n"); cur->count = MAX_DATA_POINTS; }
    printf("Enter %d data points:\n", cur->count);
    for (int i=0;i<cur->count;i++){
        printf("Point %d: ", i+1);
        scanf("%lf", &cur->data[i]);
    }
    dataset_count++;
    printf("\nDataset '%s' added successfully!\n", cur->variable_name);
}

void load_from_file(void) {
    if (dataset_count >= MAX_VARIABLES) { printf("\nMax datasets reached!\n"); return; }
    char filename[MAX_STRING];
    printf("\nEnter filename to load (e.g., sample_input.txt): ");
    scanf("%s", filename);
    FILE *f = fopen(filename, "r");
    if (!f) { printf("\nError: Could not open file '%s'\n", filename); return; }
    Dataset *cur = &datasets[dataset_count];
    printf("Enter variable name for this dataset: ");
    scanf("%s", cur->variable_name);
    cur->count = 0;
    while (fscanf(f, "%lf", &cur->data[cur->count]) == 1 && cur->count < MAX_DATA_POINTS) cur->count++;
    fclose(f);
    if (cur->count == 0) { printf("\nNo valid data found in file!\n"); return; }
    dataset_count++;
    printf("\nSuccessfully loaded %d data points from '%s'!\n", cur->count, filename);
}

void generate_sample_data(void) {
    if (dataset_count >= MAX_VARIABLES) { printf("\nMax datasets reached!\n"); return; }
    Dataset *cur = &datasets[dataset_count];
    srand((unsigned)time(NULL));
    printf("\n========= SAMPLE DATA GENERATION =========\n");
    printf("1. Normal Distribution (Sales Data)\n");
    printf("2. Uniform Distribution (Random Numbers)\n");
    printf("3. Exponential Distribution (Wait Times)\n");
    printf("Enter choice: ");
    int type; scanf("%d",&type);
    cur->count = 100;
    switch (type) {
        case 1:
            strcpy(cur->variable_name, "Sales_Data");
            for (int i=0;i<cur->count;i++){
                double u1 = (double)rand()/RAND_MAX;
                double u2 = (double)rand()/RAND_MAX;
                cur->data[i] = sqrt(-2.0*log(u1)) * cos(2 * 3.141592653589793 * u2) * 15 + 100;
            }
            break;
        case 2:
            strcpy(cur->variable_name, "Random_Numbers");
            for (int i=0;i<cur->count;i++) cur->data[i] = (double)rand()/RAND_MAX * 100;
            break;
        case 3:
            strcpy(cur->variable_name, "Wait_Times");
            for (int i=0;i<cur->count;i++){
                double u = (double)rand()/RAND_MAX;
                cur->data[i] = -log(u) * 5.0;
            }
            break;
        default:
            printf("Invalid choice!\n");
            return;
    }
    dataset_count++;
    printf("\nSample dataset '%s' generated successfully!\n", cur->variable_name);
}

void display_datasets(void) {
    if (dataset_count == 0) { printf("\nNo datasets available. Please add some data first.\n"); return; }
    printf("\n=============== CURRENT DATASETS ===============\n");
    for (int i = 0; i < dataset_count; i++) {
        printf("\nDataset %d: %s\n", i + 1, datasets[i].variable_name);
        printf("Data points: %d\n", datasets[i].count);
        printf("All values:\n");
        for (int j = 0; j < datasets[i].count; j++) {
            printf("%.2f ", datasets[i].data[j]);
            if ((j + 1) % 10 == 0) printf("\n");
        }
        printf("\n");
    }
}
