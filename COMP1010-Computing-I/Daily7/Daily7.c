
//Author: Erdun E
//Date: 02-19-2018
//Purpose: Practice using if and else.

#include <stdio.h>

int main(int argc, char* argv[]) {
    
    int number;
    printf("Please enter a positive number:  \n");
    scanf("%d",&number);
    
    while (number < 0 )
    {
        printf("Error:The number must be positive number.\nPlease enter a positive number:  \n");
        scanf("%d",&number);
    }
    if (number%2>0)
    {
        printf("The next value of the number is: %d\n",number*3+1);
    }
    else
    {
        printf("The next value of the number is: %d\n",number/2);
    }
    return 0;
}
