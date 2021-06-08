/***********************************************
 Author: Erdun E
 Date: 04-16-2018
 Purpose: Write a program that takes both the initial size of a green crud population (in pounds) and some
 number of days as input from the keyboard, and computes from that information the size of the
 population (in pounds) after the specified number of days.
 Time Spent: 3 days
 ***********************************************/

#include <stdio.h>
int main()
{
    int size, days;
    char range [100];
    while (1)
    {
        while (1)
        {
            printf("Please enter the initial size of the green curd: ");
            
            scanf("%s", &range);
            
            size = atoi(range);
            if (size <= 0){
                printf("I'm sorry that value is unrecognized or is negative.\n");
            }
            else
            {
                
                break;
                
            }
        }
        printf("please enter the number of days: ");
        scanf("%d", &days);
        
        printf("With an initial population of %d pounds of crud gorinw for %d days.\nthe final population would be %d pounds\n", size, days, result(size, days/5));
        
        while (1)
        {
            printf("Would you like to continue?(y/n): ");
            scanf("%s", &range);
            
            if (range[0]=='n')
            {
                
                return 0;
                
            }
            
            else if (range[0]=='y')
            {
                
                break;
                
            }
            
            else
            {
                
                printf("I am sorry that answer is not recognized.\n");
                
            }
        }
    }
    return 0;
}

int result(int size, int days){
    if (days <= 1)
    {
        
        return size;
        
    }
    else
    {
        
        return result(size, days-1) + result(size, days-2);
        
    }
}
