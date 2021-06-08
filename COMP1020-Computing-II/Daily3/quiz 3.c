/***********************************************************
 Author: <Erdun E>
 Date: <01-31-2019>
 Effort: <2 hours>
 Purpose: <Teach me how to replace old values  to new values in memory>
 ***********************************************************/

#include <stdio.h>

int main(int argc, const char * argv[]){
    
    unsigned int x;
    int number;
    x = 1;
    number = 0;
    for(number = 0; x != 0; number++)
    {
        printf("%d: %u", number, x);
        printf("\n");
        x = (x << 1);
    }
   
    return 0;
    
}
