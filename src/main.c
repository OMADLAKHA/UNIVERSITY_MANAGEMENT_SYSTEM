// Including all standard library and user_defined library.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "student.h"
#include "faculty.h"
#include "timetable.h"

int main(){
    srand((unsigned)time(NULL)); // Define in stdlib.h that makes your timetable different every time by randomizing subjects and slots.

    load_students();  // Read data from student, faculty and trimetable binary data.
    load_faculty();
    load_timetable();

    int ch;
    while (1){
        printf("\n=== Timetable System ===\n");
        printf("1. Add Students\n");
        printf("2. Add Faculty\n");
        printf("3. Generate Timetable\n");
        printf("4. Search Student\n");
        printf("5. Search Faculty\n");
        printf("6. Exit\n");
        printf("Choose: ");
        scanf("%d", &ch);

        if (ch == 1) add_students();
        else if (ch == 2) add_faculty();
        else if (ch == 3) generate_timetable();
        else if (ch == 4) search_student();
        else if (ch == 5) search_faculty();
        else if (ch == 6){
            save_students();  // Save all changes made in student, faculty and timetable binary file.
            save_faculty();
            save_timetable();
            printf("Saved and exiting.\n");
            break;
        }
        else {
            printf("Invalid Choice! Enter Again\n\n");
        }
    }

    return 0;
}
