#include<stdio.h>
#include<stdlib.h>
#include"my_string.h"


int main(int argc, char* argv[])
{
    MY_STRING hMy_string=NULL;
    MY_STRING hMy_string2=NULL;
    
    char* item1= "r";
    char* item2= "s";
    char* item3= "q";
    char* item4= "p";
    int n;
    
    hMy_string=my_string_init_default();
    
    my_string_push_back(hMy_string, *item1);
    my_string_push_back(hMy_string, *item2);
    my_string_push_back(hMy_string, *item3);
    
    
    printf("The string is cuurently: %s\n", my_string_at(hMy_string, 0));
    my_string_pop_back(hMy_string);
    n=my_string_empty(hMy_string);
    
    if(n==1)
    {
        printf("The string is empty!\n");
    }
    else
    {
        printf("The string is not empty!\n");
    }
    
    hMy_string2=my_string_init_default();
    my_string_push_back(hMy_string2, *item4);
    
    my_string_concat(hMy_string,hMy_string2);
    printf("The string is cuurently: %s\n", my_string_at(hMy_string, 3));

    
    my_string_destroy(&hMy_string);
    my_string_destroy(&hMy_string2);
    
    
    return 0;
    
}
