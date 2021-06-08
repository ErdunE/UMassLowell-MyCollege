/***********************************************
 Author: Erdun E
 Date: 4-11-2018
 Purpose: <learn The Collatz Conjecture>
 Time Spent: <3 days>
 ***********************************************/

#include <math.h>
#include <stdio.h>
int printOneness(int start)
{
    int steps = 0;
    while (start != 1)
    {
        steps++;
        if (start % 2 == 0)
            start = start / 2;
        else
            start = start * 3 + 1;
    }
    return steps;
}

int main() {
    int start, end;
    int count = 0;
    printf("Enter a starting point:");
    scanf("%d", &start);
    
    printf("\nEnter an ending point:");
    scanf("%d", &end);
    printf("\n");
    if (start <= 1 || start >= 1000 || end<start || end>10000)
        printf("\nOops !! Invalid input !!");
    else
    {
        for (int i = start; i <= end; i++)
        {
            printf("%5d:%-5d", i, printOneness(i));
            count++;
            if (count == 7)
            {
                printf("\n");
                count = 0;
            }
        }
    }
    return 0;
}
