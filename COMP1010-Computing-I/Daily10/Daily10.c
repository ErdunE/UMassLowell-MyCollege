/***********************************************
 Author: Erdun E
 Date: 03-09-2018
 Purpose: how to do a for loop.
 Time Spent: 1 hour
 ***********************************************/
#include <stdio.h>
void clear_keyboard_buffer(void);

void clear_keyboard_buffer(void)
{
    char ch;
    scanf("%c", &ch);
    while (ch != '\n')
    {
        scanf("%c", &ch);
    }
}

void draw_line(int);

void draw_line(int num)
{
    int i;
    for(i = 0; i < num; i++)
    {
        printf("*");
    }
    printf("\n");
}
int main(int argc, char* argv[])
{
    int number;
    printf("Please enter the number of asterisk's you want in your line: ");
    scanf("%d", &number);
    
    while (number < 1 || number > 79)
    {
        clear_keyboard_buffer();
        printf("I'm sorry, that number is unrecognized or out of range, try [1-79]: ");
        scanf("%d", &number);
    }
    
    draw_line(number);
    
    
    return 0;
}

