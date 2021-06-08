/**********************************************************************
 Program: Daily Quiz 8
 Author: Erdun E
 Date: 03-01-2019
 Time spent: 1 day
 Purpose: Based on the list of exercises stack implementation
 ***********************************************************************/
#include<stdlib.h>
#include<stdio.h>
#include"stack.h"

int main(int argc, char* argv[])
{
    char expression[256];
    char string[256];
    int i;
    
    printf("Enter what your want to test please:\n");
    fflush(stdin);

    for(i=0;;i++)
    {
        fgets(expression, sizeof expression, stdin);
        
        
        if (check_Balance(expression))
        {
            string[i]=0;
            
            printf("YES\n");
            
        }
        else
        {
            printf ("NO\n");
        }
    }
    return 0;
}

