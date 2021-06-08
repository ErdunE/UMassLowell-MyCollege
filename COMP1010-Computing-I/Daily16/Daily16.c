/***********************************************
 Author: <Erdun E>
 Date: <3-30-2018>
 Purpose: < merges the numbers in two files and writes the results to a third file.>
 Sources of Help: <tutors, web sites,friends.>
 Time Spent: <2days>
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>

void mergeTwoFiles(FILE* in1, FILE* in2, FILE* out);

int main (void)
{
    char inFileName1[20] = "numbers1.txt";
    char inFileName2[20] = "numbers2.txt";
    char outFileName[20] = "output.txt";
    
    FILE* inFile1;
    FILE* inFile2;
    FILE* outFile;
    
    if(!(inFile1 = fopen(inFileName1, "r")))
    {
        printf("Cannot open %s for input.", inFileName1);
        exit(1);
    }
    
    if(!(inFile2 = fopen(inFileName2, "r")))
    {
        printf("Cannot open %s for input.", inFileName2);
        exit(1);
    }
    
    if(!(outFile = fopen(outFileName, "w")))
    {
        printf("Cannot open %s for input.", outFileName);
        exit(1);;
    }
    
    mergeTwoFiles(inFile1, inFile2, outFile);
    
    fclose(inFile1);
    fclose(inFile2);
    fclose(outFile);
    
    return 0;
    
}

void mergeTwoFiles(FILE* inFile1, FILE* inFile2, FILE* outFile)
{
    int value1;
    int value2;
    
    fscanf(inFile1, "%d", &value1);
    fscanf(inFile2, "%d", &value2);
    
    while((!feof(inFile1)) && (!feof(inFile2)))
    {
        if(value1 <= value2)
        {
            fprintf(outFile, "%d\n", value1);
            
            fscanf(inFile1, "%d",&value1);
        }
        else
        {
            fprintf(outFile, "%d\n", value2);
            
            fscanf(inFile2, "%d",&value2);
        }
    }
    if(feof(inFile1))
    {
        while(!feof(inFile2))
        {
            fprintf(outFile, "%d\n", value2);
            fscanf(inFile2, "%d", &value2);
        }
    }
    if(feof(inFile2))
    {
        while(!feof(inFile1))
        {
            fprintf(outFile, "%d\n", value1);
            fscanf(inFile1, "%d", &value1);
        }
    }
}
