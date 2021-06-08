//
//  111.c
//  Daily9
//
//  Created by 额尔敦 on 2018/4/24.
//  Copyright © 2018年 额尔敦. All rights reserved.
//



#include <stdio.h>
#include <math.h>

void clear_keyboard_buffer(void);

void clear_keyboard_buffer(void)
{
    char ch;
    scanf("%c",&ch);
    while(ch!='\n')
    {
        scanf("%c",&ch);
    }
}



int main ()
{
    
    int number;
    
    printf("Please Enter a Negative Number : ");
    
    while(1)
    {
        scanf("%d",&number);
        
        
        if(number>0)
        {
            
            clear_keyboard_buffer();
            
            
            printf("\nI'm sorry ,you must enter a negative integer less than zero :");
            continue;
        }
        else
        {
            
            printf("The Negative Number was %d.\n",number);
            
            clear_keyboard_buffer();
            break;
        }
        
    }
    
    return 0;
}
