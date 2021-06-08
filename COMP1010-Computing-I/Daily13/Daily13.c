/***********************************************
 Author: Erdun E
 Date: 03-21-2018
 Purpose: learn do-while loop
 Sources of Help: Friend
 Time Spent: 2 hours
 ***********************************************/

#include <stdio.h>

char* convert_lengths();
char* convert_weights();

int main(void)
{
    int choice;
    do
    {
        printf("1. convert lengths\n");
        printf("2. convert weights\n");
        printf("0. Exit");
        printf("\nPlease choose from (1,2,0):\n");
        scanf("%d",&choice);
        if(choice == 1)
        {
            printf("%s",convert_lengths());
        }
        else if(choice ==2)
        {
            printf("%s",convert_weights());
        }
        else if(choice ==0)
            break;
    }while(choice != 0);
    
    return 0;
}

char* convert_lengths()
{
    return "The user wants to convert_lengths.\n\n\n";
}

char* convert_weights()
{
    return "The user wants to convert_weights.\n\n\n";
}

