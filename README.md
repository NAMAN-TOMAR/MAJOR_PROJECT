# 📊 Data Analysis & Statistics System

A statistical analysis tool I built in C for my major project. It does descriptive statistics, correlation analysis, linear regression, hypothesis testing, and some basic machine learning stuff - all from the command line.

## What This Project Does

I wanted to create something that actually helps with data analysis while learning C programming properly. So I built this system that can:

- Handle multiple datasets at once
- Calculate all the standard statistics (mean, median, std dev, etc.)
- Do correlation and regression analysis
- Detect outliers and normalize data
- Show histograms in ASCII (they look pretty cool actually!)
- Export results to CSV files

It's not as fancy as Python with pandas, but honestly, implementing everything from scratch taught me way more about how these algorithms actually work.

## Quick Start

### What You Need
- GCC compiler (I used version 11, but 7+ should work)
- A terminal
- That's it - no external libraries needed!

### Getting Started

**1. Clone this repo**
```bash
git clone https://github.com/NAMAN-TOMAR/MAJOR_PROJECT.git
cd MAJOR_PROJECT
```

**2. Compile everything**

For Linux/Mac:
```bash
gcc -o data_analysis src/*.c -Iinclude -std=c99 -Wall -Wextra -lm
```

For Windows (using MinGW):
```bash
gcc -o data_analysis.exe src/*.c -Iinclude -std=c99 -Wall -Wextra -lm
```

**3. Run it**
```bash
./data_analysis
```

## How to Use It

### Example 1: Quick Analysis

Let's say you want to analyze some sales data:

1. Run the program
2. Go to "Data Input & Management" (option 1)
3. Choose "Manual Data Entry" (option 1)
4. Enter your numbers when prompted
5. Go back and select "Statistical Analysis" (option 2)
6. Pick "Descriptive Statistics" to see all the stats

That's it! You'll get mean, median, standard deviation, quartiles, and everything else.

### Example 2: Loading Data from a File

Create a text file with your numbers (one per line):
```
150.5
200.3
180.7
220.1
195.8
```

Then in the program:
- Option 1 → Option 2 → Enter filename
- Done! Your data is loaded.

### Example 3: Finding Correlations

This is useful when you want to see if two variables are related:

1. Load two datasets (or enter them manually)
2. Go to Statistical Analysis → Correlation Analysis
3. Select your two datasets
4. The program tells you if they're strongly, moderately, or weakly correlated

I used this to analyze temperature vs sales data for one of my examples - worked great!

## Features I Implemented

### Data Management
- Manual data entry (good for small datasets)
- File loading (saves time for bigger datasets)
- Sample data generation - I added three types:
  - Normal distribution (like sales data)
  - Uniform distribution (random numbers)
  - Exponential distribution (wait times)
- You can work with up to 10 datasets at once

### Statistical Analysis
The math stuff took me a while to get right:
- Basic stats (mean, median, mode - though mode isn't fully done yet)
- Standard deviation and variance
- Quartiles and IQR (for box plots)
- Correlation analysis with Pearson's r
- Linear regression (with predictions!)
- Hypothesis testing (one-sample t-test)
- Confidence intervals (95% and 99%)

### Machine Learning Basics
I kept this simple but functional:
- Z-score normalization (standardizes your data)
- Outlier detection using the IQR method
- Train-test splitting
- Simple prediction model

### Visualization
ASCII histograms! They actually look decent:
```
======== HISTOGRAM ========
150.50-157.46: ** (2)
157.46-164.42: *** (3)
164.42-171.38: **** (4)
...
```

Not as pretty as matplotlib, but it gets the job done.

## Project Structure

I organized everything into modules to keep it clean:

```
MAJOR_PROJECT/
│
├── include/          # All the header files
│   ├── dataset.h    # Data structures
│   ├── io.h         # Input/output stuff
│   ├── stats.h      # Statistics functions
│   ├── ml.h         # ML functions
│   ├── utils.h      # Helper functions
│   └── visualization.h
│
├── src/             # Implementation files
│   ├── main.c       # Entry point
│   ├── io.c         # Menu system and I/O
│   ├── stats.c      # All the math
│   ├── ml.c         # ML implementations
│   ├── utils.c      # Sorting, etc.
│   └── visualization.c
│
└── docs/ flowchart
└──       projectreport.txt
└── sample_input.txt
└── README.md        # You're reading it!
```

## Some Technical Details

### Data Structures
I used two main structures:

```c
typedef struct {
    char variable_name[100];
    double data[1000];      // Can hold up to 1000 points
    int count;
} Dataset;

typedef struct {
    double mean, median, mode;
    double std_deviation, variance;
    double min, max, range;
    double q1, q2, q3, iqr;
} Statistics;
```

### Algorithms
- For sorting (needed for median/quartiles), I used bubble sort. Yeah, it's O(n²), but for small datasets it's fine and easy to understand.
- Correlation uses Pearson's formula
- Regression uses the least squares method
- Outlier detection uses the 1.5×IQR rule

## Things That Could Be Better

Being honest about limitations:
- Only handles 1000 points per dataset (could make this dynamic with malloc)
- Maximum 10 datasets (same thing)
- Visualization is ASCII only (would love to add actual graphs)
- Only reads plain text files (CSV support would be nice)
- Mode calculation isn't complete (it's on my TODO list)
- Bubble sort is slow for large datasets
- No way to save your work between sessions

## What I'd Add Next

If I had more time (or for version 2.0):
- [ ] Actual graphical plots using gnuplot
- [ ] CSV file support
- [ ] Save/load sessions
- [ ] More statistical tests (ANOVA, chi-square)
- [ ] Better sorting algorithm (quicksort)
- [ ] GUI maybe? (GTK or something)
- [ ] More ML stuff (k-means clustering would be cool)

## Sample Output

Here's what the stats output looks like:

```
========== DESCRIPTIVE STATISTICS ==========
Variable: Sales_Data
─────────────────────────────────────────────
Mean:                 189.48
Median:               195.80
Standard Deviation:   26.85
Variance:             721.25
Minimum:              150.50
Maximum:              220.10
Range:                69.60
First Quartile (Q1):  180.70
Third Quartile (Q3):  200.30
Interquartile Range:  19.60
═════════════════════════════════════════════
```

Pretty clean, right?

## A Note About the Code

Full transparency: I used ChatGPT and GitHub Copilot while working on this project. Mainly for:
- Making sure my statistical formulas were correct (didn't want to mess up the math!)
- Help with error handling patterns
- Debugging some tricky pointer issues
- Code formatting and optimization

But the overall design, architecture, feature choices, and all the learning - that was all me. The comments throughout the code show my actual thought process and learning journey.

## Testing

I tested this with various datasets:
- Small datasets (5-10 points) for quick verification
- Generated normal distributions to test histogram
- Real sales data for correlation analysis
- Edge cases (empty data, single point, etc.)

Everything compiles with zero warnings using `-Wall -Wextra` flags.

## Why C Instead of Python?

Good question! A few reasons:
1. Wanted to really understand what's happening under the hood
2. C forces you to think about memory and efficiency
3. It's actually faster for large datasets
4. Good practice for systems programming
5. More impressive? (hopefully!)

Plus, implementing everything from scratch means I actually learned how correlation, regression, etc. work, not just how to call numpy functions.

## Contributing

If you want to improve this or add features, feel free to fork and submit a PR! Some ideas:
- Add that CSV support
- Implement more statistical tests
- Improve the visualization
- Add better sorting algorithms
- Fix the mode calculation

## About Me

**Naman Tomar**  
SAP ID: 590024327  
Batch: 37

This was my major project for [1st semester]. It took about 3-4 weeks of actual work (plus a lot of debugging time!).

## Issues?

If something doesn't work:
1. Make sure you compiled with `-lm` flag (needed for math functions)
2. Check that you're in the right directory when loading files
3. Try the sample data generation if file loading isn't working
4. Open an issue on GitHub if you're stuck




---

**Status:** Working and tested on Windows 11, Ubuntu 22.04, and macOS

**Last Updated:** December 2024

---

*Built with C, math, and a lot of coffee ☕*

*"Simple things should be simple, complex things should be possible." 
