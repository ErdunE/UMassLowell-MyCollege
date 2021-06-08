/***********************************************
 Author: Erdun E
 Date: 02-12-2017
 Answer to question:It's probably because there's not enough memory, and it stops at half.
 ***********************************************/



#include <stdio.h>

void recursive_down_to_zero(int);
void recursive_up_to_int(int);

int main() {
    
    int number;
    
    printf("Please enter a positive number:  \n");
    scanf("%d",&number);
    recursive_down_to_zero(number);
    printf("****\n");
    recursive_up_to_int(number);
    
    return 0;
}

void recursive_down_to_zero(int num){
    if(num >= 0)
    {
        printf("%d\n", num);
        recursive_down_to_zero(num - 1);
    }
}

void recursive_up_to_int(int num){
    
    if(num >=0)
    {
        recursive_up_to_int(num - 1);
        printf("%d\n",num);
    }
}

