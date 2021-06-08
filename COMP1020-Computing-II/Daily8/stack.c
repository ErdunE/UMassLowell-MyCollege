#include<stdlib.h>
#include<stdio.h>
#include"stack.h"

void stack_init_defualt(struct stack* temp)
{
    temp = NULL;
}

struct stack* stack_push(struct stack *temp1,char temp2)
{
    struct stack* temp3 = (struct stack*)malloc(sizeof(struct stack));
    
    if(temp3 == NULL)
    {
        exit(0);
    }
    
    temp3->data = temp2;
    
    temp3->next = temp1;
    
    temp1 = temp3;
    
    return temp1;
}


int stack_empty(struct stack *temp)
{
    return temp == NULL ?
    1 : 0;
}

struct stack* stack_pop(struct stack *temp1, char *temp2)
{
    struct stack* temp3 = temp1;
    
    *temp2 = temp1->data;
    
    temp1 = temp1->next;
    
    free(temp3);
    
    return temp1;
}




int check_matching(char Lift_Side, char Right_Side)
{
    if (Lift_Side == '[' && Right_Side == ']')
        return 1;
    
    else if (Lift_Side == '(' && Right_Side == ')')
        return 1;
    
    else if (Lift_Side == '{' && Right_Side == '}')
        return 1;
    
    else
        return 0;
}

int check_Balance(char expression[])
{
    int i = 0;
    char n;
    struct stack *temp=NULL;
    
    stack_init_defualt(temp);
    
    while (expression[i])
    {
        if (expression[i] == '{' || expression[i] == '(' || expression[i] =='[')
            temp = stack_push(temp, expression[i]);
       
        if (expression[i] == '}' || expression[i] == ')' || expression[i] ==']')
        {
            if (stack_empty(temp))
                return 0;
            
            else
            {
                temp = stack_pop(temp,&n);
                
                if ( !check_matching(n,expression[i]) )
                    return 0;
            }
        }
        
        i++;
    }
    
    if (temp == NULL)
        return 1;
    else
        return 0;
}
