/* Making a header file name "student.h" that declares all data of student.

It contain: 1:- Structure name Student that declares Student data.
            2:- Three Global variable that contains
                array of student data , total number of student, id of student.
            3:- 4 function to add or search and display student data.

Use by: 1:- main.c
        2:- timetable.c (because timetable prints student batch timetable)
*/

#ifndef STUDENT_H
#define STUDENT_H

#include "common.h" // Including common.h header file that we make earlier to access macros made by define and DOB structure.

typedef struct {
    int student_id;
    char name[MAX_NAME];
    DOB dob;
    int batch;
} Student;

extern Student students[MAX_STUDENTS];  // Creating a array of Student structure name students
extern int student_count;
extern int next_student_id;

void add_students();
void search_student();
void save_students();
void load_students();

#endif
