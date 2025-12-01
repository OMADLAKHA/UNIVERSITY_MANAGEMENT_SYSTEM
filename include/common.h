/* Making a header file name "common.h" that contains all global constants and shared data types used across the entire project.

It includes: 1:- Maximum limits of (students, batches, faculty, etc.)
             2:- Total days, slots, subjects
             3:- DOB structure to store date of birth of student
             4:- Arrays for subject names and day names (declared as extern)

Use by: Every other header and C file.
*/

#ifndef COMMON_H
#define COMMON_H

#define MAX_STUDENTS 750
#define MAX_FACULTY 40
#define MAX_NAME 50
#define MAX_BATCHES 25
#define MAX_STUDENTS_PER_BATCH 30
#define SUBJECT_COUNT 5
#define DAYS 6
#define SLOTS 10     // Slots tell how many hour a day the classes will held
#define MIN_PERIODS 2
#define MAX_PERIODS 4

extern const char *subjects[SUBJECT_COUNT];  // Creating a Global Array
extern const char *daynames[DAYS];

// extern tells the compiler that a variable or function exists somewhere else, not in the current file.

typedef struct {
    int day, month, year;
} DOB;

#endif
