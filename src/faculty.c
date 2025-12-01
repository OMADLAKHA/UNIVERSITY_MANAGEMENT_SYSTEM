#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "faculty.h"
#include "timetable.h"

Faculty fac[MAX_FACULTY];
int faculty_count = 0;
int next_faculty_id = 1;

static void flush_stdin(){  // It clears leftover input from the keyboard buffer so the next input works correctly.
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

static int randint(int a, int b){
    return a + rand() % (b - a + 1);
}

static int ci_equal(const char *a, const char *b){  // // Compare strings and convert uppercase to lowercase.
    while (*a && *b){
        char x = *a, y = *b;
        if (x >= 'A' && x <= 'Z') x += 32;
        if (y >= 'A' && y <= 'Z') y += 32;
        if (x != y) return 0;
        a++; b++;
    }
    return *a == 0 && *b == 0;
}

void save_faculty(){
    FILE *f = fopen("facultyB.dat","wb");
    if (!f) return;
    fwrite(&faculty_count, sizeof(int), 1, f);
    fwrite(&next_faculty_id, sizeof(int), 1, f);
    fwrite(fac, sizeof(Faculty), faculty_count, f);
    fclose(f);
}

void load_faculty(){
    FILE *f = fopen("facultyB.dat","rb");
    if (!f) return;
    fread(&faculty_count, sizeof(int), 1, f);
    fread(&next_faculty_id, sizeof(int), 1, f);
    fread(fac, sizeof(Faculty), faculty_count, f);
    fclose(f);
}

void add_faculty(){
    int n;
    printf("How many faculty? ");
    scanf("%d", &n);
    flush_stdin();

    for (int i=0;i<n;i++){
        if (faculty_count >= MAX_FACULTY){
            printf("Limit reached.\n");
            break;
        }

        Faculty F;
        F.faculty_id = next_faculty_id++;

        printf("Enter name: ");
        fgets(F.name, MAX_NAME, stdin);
        F.name[strcspn(F.name, "\n")] = 0;

        printf("Choose subject:\n\n");
        for (int s=0;s<SUBJECT_COUNT;s++)
            printf("%d. %s\n", s+1, subjects[s]);

        printf("\n");
        int c;
        printf("Enter Subject Number the Faculty teaches: ");
        scanf("%d", &c);

        if (c > SUBJECT_COUNT) {
            printf("Invalid Option. Please Select Again\n");

            printf("Enter Subject Number the Faculty teaches: ");
            scanf("%d", &c);
        }
        flush_stdin();
        F.subject_id = c - 1;

        fac[faculty_count++] = F;

        printf("\n");
    }

    save_faculty();
}

int random_faculty_for_subject(int subj){
    int list[MAX_FACULTY], count = 0;
    for (int i=0;i<faculty_count;i++){
        if (fac[i].subject_id == subj)
            list[count++] = fac[i].faculty_id;
    }
    if (count == 0) return 0;

    return list[rand() % count];
}

void search_faculty(){
    char faculty_name[MAX_NAME];
    printf("Enter faculty name: ");
    flush_stdin();
    fgets(faculty_name, MAX_NAME, stdin);
    faculty_name[strcspn(faculty_name, "\n")] = 0;

    printf("\n");

    for (int i=0;i<faculty_count;i++){
        if (ci_equal(faculty_name, fac[i].name)){
            print_faculty_timetable_grouped(fac[i].faculty_id);
            return;
        }
    }
    printf("Not found.\n");
}
