#include <stdio.h>
#include <string.h>
#include "student.h"
#include "timetable.h"

Student students[MAX_STUDENTS];
int student_count = 0;
int next_student_id = 1000;

static void flush_stdin(){   // It clears leftover input from the keyboard buffer so the next input works correctly.
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

static int ci_equal(const char *a, const char *b){  // Compare strings and convert uppercase to lowercase.
    while (*a && *b){
        char x = *a, y = *b;
        if (x >= 'A' && x <= 'Z') x += 32;
        if (y >= 'A' && y <= 'Z') y += 32;
        if (x != y) return 0;
        a++; b++;
    }
    return *a == 0 && *b == 0;
}

void save_students(){
    FILE *f = fopen("studentsB.dat","wb");
    if (!f) return;
    fwrite(&student_count, sizeof(int), 1, f);
    fwrite(&next_student_id, sizeof(int), 1, f);
    fwrite(students, sizeof(Student), student_count, f);
    fclose(f);
}

void load_students(){
    FILE *f = fopen("studentsB.dat","rb");
    if (!f) return;
    fread(&student_count, sizeof(int), 1, f);
    fread(&next_student_id, sizeof(int), 1, f);
    fread(students, sizeof(Student), student_count, f);
    fclose(f);
}

void add_students(){
    int n;
    printf("How many students? ");
    if (scanf("%d", &n) != 1){ 
        flush_stdin(); 
        return; 
    }
    flush_stdin();

    for (int i=0;i<n;i++){
        if (student_count >= MAX_STUDENTS){
            printf("Limit reached.\n");
            break;
        }

        Student S;
        S.student_id = next_student_id++;

        printf("Enter name: ");
        fgets(S.name, MAX_NAME, stdin);
        S.name[strcspn(S.name, "\n")] = 0;  // strcspn() removes extra \n for clear result.

        printf("DOB (DD-MM-YYYY): ");
        scanf("%d-%d-%d", &S.dob.day, &S.dob.month, &S.dob.year);
        flush_stdin();

        S.batch = (student_count / MAX_STUDENTS_PER_BATCH) + 1;
        students[student_count++] = S;

        printf("\n");
    }

    save_students();
}

void search_student(){
    char student_name[MAX_NAME];
    printf("Enter student name: ");
    flush_stdin();
    fgets(student_name, MAX_NAME, stdin);
    student_name[strcspn(student_name, "\n")] = 0;

    for (int i=0;i<student_count;i++){
        if (ci_equal(student_name, students[i].name)){
            printf("\nStudent: %s(Id: %d), Batch %d\n", students[i].name, students[i].student_id, students[i].batch);
            printf("\n");
            print_batch_timetable(students[i].batch);
            return;
        }
    }
    printf("Not found.\n");
}

