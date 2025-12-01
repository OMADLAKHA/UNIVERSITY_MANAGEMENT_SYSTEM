#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "timetable.h"
#include "faculty.h"
#include "student.h"
#include "common.h"

Cell timetable[MAX_BATCHES][DAYS][SLOTS];

/* Subject names */
const char *subjects[SUBJECT_COUNT] = {
    "Advanced Engineering Mathematics", "Programming in C", "Linux Lab", "Problem Solving", "E.V.S"
};

/* Day names */
const char *daynames[DAYS] = {
    "Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"
};

int randint(int a, int b){
    return a + rand() % (b - a + 1);
}

/* Count how many batches a faculty teaches at the same time */
int faculty_slot(int faculty_id, int day, int slot){
    int count = 0;

    for (int b = 0; b < MAX_BATCHES; b++){
        if (timetable[b][day][slot].faculty_id == faculty_id){
            count++;
        }
    }
    return count;     /* Maximum allowed = 2 */
}

void save_timetable(){
    FILE *f = fopen("timetableB.dat","wb");
    if (!f) return;

    fwrite(timetable, sizeof(Cell), MAX_BATCHES * DAYS * SLOTS, f);
    fclose(f);
}

void load_timetable(){
    FILE *f = fopen("timetableB.dat","rb");
    if (!f){
        /* initialize empty timetable */
        for (int b=0; b<MAX_BATCHES; b++)
            for (int d=0; d<DAYS; d++)
                for (int s=0; s<SLOTS; s++){
                    timetable[b][d][s].subject_id = -1;
                    timetable[b][d][s].faculty_id = 0;
                    timetable[b][d][s].hour = 8 + s;
                }
        return;
    }

    fread(timetable, sizeof(Cell), MAX_BATCHES * DAYS * SLOTS, f);
    fclose(f);
}

void generate_timetable(){

    /* clear timetable first */
    for (int b=0; b<MAX_BATCHES; b++)
        for (int d=0; d<DAYS; d++)
            for (int s=0; s<SLOTS; s++){
                timetable[b][d][s].subject_id = -1;
                timetable[b][d][s].faculty_id = 0;
                timetable[b][d][s].hour = 8 + s;
            }

    /* generate timetable */
    for (int b=0; b<MAX_BATCHES; b++){
        for (int d=0; d<DAYS; d++){

            int periods = randint(MIN_PERIODS, MAX_PERIODS);
            int used[SLOTS] = {0};
            int done = 0;

            while (done < periods){
                int slot = randint(0, SLOTS-1);
                if (used[slot]) continue;
                used[slot] = 1;

                int subj = randint(0, SUBJECT_COUNT-1);
                int assigned_faculty = 0;

                /* Try to find a faculty who is free (max 2 loads allowed) */
                for (int try = 0; try < 20; try++){
                    int fid = random_faculty_for_subject(subj);
                    if (fid == 0) break;

                    if (faculty_slot(fid, d, slot) < 2){
                        assigned_faculty = fid;
                        break;
                    }
                }

                timetable[b][d][slot].subject_id = subj;
                timetable[b][d][slot].faculty_id = assigned_faculty;

                done++;
            }
        }
    }

    save_timetable();
    printf("Timetable generated.\n");
}

void print_batch_timetable(int batch){
    if (batch < 1 || batch > MAX_BATCHES){
        printf("Invalid batch.\n");
        return;
    }

    int b = batch - 1;

    for (int d=0; d<DAYS; d++){
        printf("%s:\n", daynames[d]);

        int any = 0;

        for (int s=0; s<SLOTS; s++){
            if (timetable[b][d][s].subject_id != -1){
                any = 1;

                int hour = timetable[b][d][s].hour;
                int subj = timetable[b][d][s].subject_id;
                int fid = timetable[b][d][s].faculty_id;

                char fname[MAX_NAME] = "TBA";

                if (fid != 0){
                    for (int i=0; i<faculty_count; i++){
                        if (fac[i].faculty_id == fid){
                            strcpy(fname, fac[i].name);
                            break;
                        }
                    }
                }

                printf("  %02d:00-%02d:00  %s (%s)\n",
                       hour, hour+1, subjects[subj], fname);
            }
        }
        printf("\n");

        if (!any) printf("  No classes\n");
    }
}

void print_faculty_timetable_grouped(int faculty_id){

    int fidx = -1;
    for (int i=0; i<faculty_count; i++){
        if (fac[i].faculty_id == faculty_id){
            fidx = i;
            break;
        }
    }

    if (fidx == -1){
        printf("Faculty not found.\n");
        return;
    }

    printf("Faculty: %s (Subject: %s)\n",
           fac[fidx].name,
           subjects[fac[fidx].subject_id]);

    for (int d=0; d<DAYS; d++){
        printf("%s:\n", daynames[d]);

        int any = 0;

        for (int s=0; s<SLOTS; s++){
            int batches[3];
            int count = 0;

            for (int b=0; b<MAX_BATCHES; b++){
                if (timetable[b][d][s].faculty_id == faculty_id){
                    if (count < 2){            /* show max 2 only */
                        batches[count] = b + 1;
                    }
                    count++;
                }
            }

            if (count > 0){
                any = 1;
                int hour = 8 + s;

                printf("  %02d:00-%02d:00  %s (Batches: ",
                       hour, hour+1, subjects[fac[fidx].subject_id]);

                int show = count;
                if (show > 2) show = 2;        /* print max 2 */

                for (int k=0; k<show; k++){
                    printf("%d", batches[k]);
                    if (k+1 < show) printf(", ");
                }

                printf(")\n");
            }
        }
        printf("\n");

        if (!any) printf("  No classes\n");
    }
}
