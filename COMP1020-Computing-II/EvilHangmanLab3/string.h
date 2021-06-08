#ifndef string_h

#define string_h

#include <stdlib.h>

//define the status

#define SUCCESS 1

#define FAILURE 0

typedef void * MY_STRING;

typedef int Status;

MY_STRING my_string_init_default(void)

{
    
    char* hMy_string = (char*)malloc(7); //can store upto 7 characters
    
    if(hMy_string != NULL)
        
        hMy_string[0] = '\0' ; //initialize to empty string
    
    
    
    return hMy_string;
    
}

MY_STRING my_string_init_c_string(const char* c_string)

{
    
    int len = 0, i;
    
    while(c_string[len] != '\0')
        
        len++;
    
    
    
    char* hMy_string = (char*)malloc(len + 1 );
    
    for(i = 0; i <= len; i ++)
        
        hMy_string[i] = c_string[i];
    
    return hMy_string;
    
}

int my_string_get_capacity(MY_STRING hMy_string)

{
    
    return sizeof(hMy_string); //returns the maximum allocated space for this handle
    
}

int my_string_get_size(MY_STRING hMy_string)

{
    
    char* str = (char *) hMy_string;
    
    int size = 0;
    
    while(str[size] != '\0') //loop till we find a \0
        
        size++;
    
    return size;
    
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)

{
    
    int len1 = my_string_get_size(hLeft_string);
    
    int len2 = my_string_get_size(hRight_string);
    
    int i = 0;
    
    char *s1 = hLeft_string, *s2 = (char*)hRight_string;
    
    while ( i < len1 && i < len2)
        
    {
        
        //return a value when mismatch -1 when left is less than right, 1 if left is more than right
        
        if(s1[i] < s2[i])
            
            return -1;
        
        else if(s1[i] > s2[i])
            
            return 1;
        
        else //correponding characters matched, moveon to next location
            
            i++;
        
    }
    
    
    
    if(len1 == len2)
        
        return 0;
    
    else if(len1 < len2)
        
        return -1;
    
    else
        
        return 1;
    
    
    
}

Status my_string_extraction(MY_STRING hMy_string, FILE *fp)

{
    
    long start = 0, end = 0;
    
    char ch;
    
    int len ,capacity, i ;
    
    while(!feof(fp))
        
    {
        
        ch = fgetc(fp);
        
        
        
        if(ch== ' ' || ch == '\t' || ch == '\n' || ch == '\r') //whitespace characters
            
            continue;
        
        else
            
        {
            
            start = ftell(fp) - 1;
            
            end = start + 1;
            
            break;
            
        }
        
    }
    
    
    
    if(end == 0)
        
        return FAILURE;
    
    
    
    while(!feof(fp))
        
    {
        
        ch = fgetc(fp);
        
        end++;
        
        if(ch== ' ' || ch == '\t' || ch == '\n' || ch == '\r') //whitespace characters
            
            break;
        
    }
    
    
    
    
    
    
    
    len = (int)(end - start - 1);
    
    if(len == 0)
        
        return FAILURE;
    
    
    
    capacity = my_string_get_capacity(hMy_string);
    
    if(len >= capacity) //need to allocate more space?
        
    {
        
        hMy_string = realloc(hMy_string, len + 1); //should return this new address ?
        
    }
    
    
    
    fseek(fp, start, SEEK_SET);
    
    char* str = (char*)hMy_string;
    
    for(i = 0; i < len; i++)
        
        str[i] = fgetc(fp);
    
    str[i] = '\0';
    
    
    
    return SUCCESS;
    
    
    
}

Status my_string_insertion(MY_STRING hMy_string, FILE *fp)

{
    
    if(fprintf(fp,"%s", hMy_string))
        
        return SUCCESS;
    
    else
        
        return FAILURE;
    
}

void my_string_destroy(MY_STRING* hMy_string)

{
    
    free(*hMy_string);
    
    *hMy_string = NULL;
    
}

#endif /* string_h */
