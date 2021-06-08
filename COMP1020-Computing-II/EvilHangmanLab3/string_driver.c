#include <stdio.h>

#include "string.h"

int main(int argc, char* argv[])

{
    
    MY_STRING hMy_string = NULL;
    
    FILE *fp;
    
    
    
    hMy_string = my_string_init_default();
    
    fp = fopen("/Users/ErdunE/Desktop/COMP 1020/LAB3/LAB3/simple.txt", "r");
    
    if(fp == NULL)
        
    {
        
        printf("\nCould not open simple.txt\n");
        
        return -1;
        
    }
    
    while(my_string_extraction(hMy_string, fp))
        
    {
        
        my_string_insertion(hMy_string, stdout);
        
        printf("\n");
        
        if(fgetc(fp) == ' ')
            
        {
            
            printf("Found a space after the string\n");
            
        }
        
    }
    
    my_string_destroy(&hMy_string);
    
    fclose(fp);
    
    return 0;
    
}
