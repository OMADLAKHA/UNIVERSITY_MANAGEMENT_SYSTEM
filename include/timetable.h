/* Making a header file name "timetable.h" that declares the structure and functions used for the timetable system.

It contains: 1:- Structure name cell to assign student to class teach by faculty in a particular hour.
             2:- A Global Variable that contains timetable in the form of 3-D array.
             3:- 5 functions to genearet and display student(of batch) and faculty timetable.

Used by: 1:- main.c
         2:- student.c (printing timetable for student)
         3:- faculty.c (printing timetable for faculty)
*/

#ifndef TIMETABLE_H
#define TIMETABLE_H

#include "common.h" // Including common.h header file that we make earlier to access macros made by define.

typedef struct {
    int subject_id;
    int faculty_id;
    int hour;
} Cell;

extern Cell timetable[MAX_BATCHES][DAYS][SLOTS];

void generate_timetable();
void save_timetable();
void load_timetable();

void print_batch_timetable(int batch);
void print_faculty_timetable_grouped(int faculty_id);

#endif
