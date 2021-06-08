/***********************************************
 Author: <Erdun E>
 Date: <3-26-2018>
 Sources of Help: <tutors, web sites, lab assistants，friends>
 Time Spent: <5 hours>
 ***********************************************/

#include <stdio.h>
#include <ctype.h>


int get012() {
    int choice = ((int)getchar()) - 48;
    while ( ! (choice == 0 || choice == 1 || choice == 2)) {
        printf("\nPlease choose from (1,2,0):\n");
        choice = ((int)getchar()) - 48;
    }
    return choice;
}

char* length_to_us() {
    return "length to us";
}
char* length_to_metric() {
    return "length to metric";
}
char* weight_to_us() {
    return "weight to us";
}
char* weight_to_metric() {
    return "weight to metric";
}
char* convert_lengths()
{
    int choice;
        
    printf("convert lengths from\n");
    printf("1. feet/inches to meters/centimeters\n");
    printf("2. meters/centimeters to feet/inches\n");
    printf("0. no longer wants to convert length measurements\n");
    printf("Please choose from(1,2,0):\n");
    choice = get012();
    
    if(choice == 1)
    {
        return length_to_metric();
    }
    else if(choice ==2)
    {
        return length_to_us();
    }
    else
        return "The user no longer wants to convert_lengths.\n\n\n";
}

char* convert_weights()
{
    int choice;
    
    printf("convert weights from\n");
    printf("1. pounds/ounces to kilograms/grams\n");
    printf("2. kilograms/grams to pounds/ounces\n");
    printf("0. no longer wants to convert weight measurements");
    printf("Please choose from(1,2,0):\n");
    choice = get012();
    
    
    if(choice == 1)
    {
        return weight_to_metric();
    }
    else if(choice ==2)
    {
        return weight_to_us();
    }
    else
        return " the user no longer wants to convert weight measurements.\n";
}

int main(void)
{
    int choice;
    
    
    printf("1. convert lengths\n");
    printf("2. convert weights\n");
    printf("0. Exit\n");
    printf("Please choose from (1,2,0):\n");
    choice = get012();
    
    if(choice == 1)
    {
        printf("%s",convert_lengths());
    }
    else if(choice ==2)
    {
        printf("%s",convert_weights());
    }
    else if(choice ==0)
        printf("quit");
    
    return 0;
}

