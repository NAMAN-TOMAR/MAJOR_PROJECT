#ifndef IO_H
#define IO_H

#include "dataset.h"
/*
Menu declarations 
*/
void display_main_menu(void);// main navigation hub
void data_input_menu(void);// handles loading/typing data
void statistical_analysis_menu(void);// bunch of stats routines will live here... eventually
void visualization_menu(void);// graphs/plots
void machine_learning_menu(void);
void data_export_menu(void);// exporting options (CSV)

/* Input operations
Data-related operations.
*/
void manual_data_entry(void);; // basic numeric input;
void load_from_file(void);// NOTE: file parsing is still a bit fragile
void generate_sample_data(void);
void display_datasets(void);// prints whatever datasets we have;

#endif /* IO_H */
