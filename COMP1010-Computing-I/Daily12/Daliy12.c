/***********************************************
 Author: Erdun E
 Date: 03-19-2018
 Purpose: Set the loop and find the maximum tolerances in the two Numbers.
 Time Spent: 1 hours
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>
int readValidInteger()
{
    char temp[10];
    scanf("%d", &temp);
    while(atoi(temp) <= 0)
    {
        printf("I'm sorry that number is unrecognized or not positive.\n");
        printf("Please enter a positive integer: \n");
        scanf("%d", &temp);
    }
    return atoi(temp);
}

int method(int n1, int n2)
{
    int i;
    if(n1 > n2)
        i = n2;
    else
        i = n1;
    while(n1 % i != 0 || n2 % i != 0)
        i--;
    return i;
    
}

int main()
{
    int num1, num2;
    printf("Please enter a positive integer: \n");
    num1 = readValidInteger();
    printf("Please enter a second positive integer: \n");
    num2 = readValidInteger();
    int value = method(num1, num2);
    printf("The largest integer that divides both %i and %i is: %i\n", num1, num2, value);
}

