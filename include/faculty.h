/* Making a header file name "faculty.h" that declares all data of faculty.

It contain: 1:- Structure name faculty that declares faculty data.
            2:- Three Global variable that contains
                array of faculty data , total number of faculty, id of faculty.
            3:- 5 function to add or search and display faculty data with the subject they teach.

Use by: 1:- main.c
        2:- timetable.c (for assigning faculty)
*/

#ifndef FACULTY_H
#define FACULTY_H

#include "common.h" // Including common.h header file that we make earlier to access macros made by define.

typedef struct {
    int faculty_id;
    char name[MAX_NAME];
    int subject_id;
} Faculty;

extern Faculty fac[MAX_FACULTY];  // Creating a array of faculty structure name fac
extern int faculty_count;
extern int next_faculty_id;

// Declaring functions to store faculty record like adding or showing faculty record with the subject they teach.
void add_faculty();                         
void search_faculty();
void save_faculty();
void load_faculty();
int random_faculty_for_subject(int subj);

#endif
