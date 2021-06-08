#ifndef STACK_H
#define STACK_H


struct stack{char data;struct stack* next;};
struct stack* stack_push(struct stack *temp1,char temp2);
struct stack* stack_pop(struct stack *temp1,char *temp2);

void stack_init_defualt(struct stack* temp);

int stack_empty(struct stack *temp);
int check_matching(char Lift_Side, char Right_Side);
int check_Balance(char expression[]);


#endif
