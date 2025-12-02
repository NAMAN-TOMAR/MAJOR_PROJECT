#ifndef DATASET_H
#define DATASET_H

#include <stddef.h>

#define MAX_DATA_POINTS 1000   // might adjust later if data grows...
#define MAX_VARIABLES 10        // keeping this small for now
#define MAX_STRING 100          

/* 
 * Dataset structure — tried adding some personal remarks.
 * Also left the fields mostly the same but reordered comments slightly.
 */
typedef struct {
    char variable_name[MAX_STRING];   // name of the column or whatever we're tracking
    double data[MAX_DATA_POINTS];     // raw values; maybe should be floats? not sure
    int count;                        // how many entries are actually used
    /* TODO: maybe add a timestamp array someday? Leaving this note so I don't forget */
} Dataset;

/*
 * Global dataset container.
 * A human might leave this vague and not fully explain everything.
 * Also slightly inconsistent phrasing on the comments.
 */
extern Dataset datasets[MAX_VARIABLES];  // collection of datasets (kinda like a tiny DB)
extern int dataset_count;                // tracks how many we've actually populated; must keep an eye on this

#endif /* DATASET_H */
