/*
 Author: Erdun E
 Course: COMP1010, Computing I
 Date: 05-03-2018
 Description: This file implements the functionality required by Programming_Quiz 3.
 */
#include<stdio.h>
#include<stdlib.h>

void Read(FILE *fr, char fname[], char lname[], int quiz[])
{
    int c;

    for(c = 0; c < 10; c++)
        quiz[c] = 0;

    fscanf(fr, "%s %s", fname, lname);

    for(c = 0; c < 10; c++)
        fscanf(fr, "%d", &quiz[c]);
}

void Write(FILE *fw, char fname[], char lname[], int quiz[])
{
    int c, sum = 0;
    float avg;

    fprintf(fw, "%-20s %-20s ", lname ,fname );

    for(c = 0; c < 10; c++)
    {
        fprintf(fw, "%4d ", quiz[c]);
        sum += quiz[c];
    }

    avg = sum / 10;

    fprintf(fw, "%6.2f ", avg);

    fprintf(fw,"\n");
}

int main()
{

    FILE *fr, *fw;

    fr = fopen("Quiz.txt", "r");

    fw = fopen("Average.txt", "w");
    char fname[20], lname[20];
    int quiz[10], avg, c = 0;
    char avgs[10];

    if (fr == NULL)
    {
        printf("I couldn't open Quiz.txt for reading.\n");
        exit(0);
    }
    else
    {

        fprintf(fw, "%-20s %-20s %4s %4s %4s %4s %4s %4s %4s %4s %4s %4s %10s", "LastName", "FirstName", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Average \n");

        while (!feof(fr))
        {

            Read(fr, fname, lname, quiz);

            Write(fw, fname, lname, quiz);
        }
    }

    fclose(fr);
    fclose(fw);

    fr = fopen("Average.txt", "r");

    fw = fopen("Quiz.txt", "w");

    while (!feof(fr))
    {
 
        fscanf(fr, "%s %s", fname, lname);
        for(c = 0; c < 10; c++)
            fscanf(fr, "%d", &quiz[c]);
        fscanf(fr, "%s", avgs);
 
        fprintf(fw, "%-20s %-20s ", lname ,fname );
        for(c = 0; c < 10; c++)
            fprintf(fw, "%4d ", quiz[c]);
        fprintf(fw, "%6s ", avgs);
        fprintf(fw,"\n");
    }
}
