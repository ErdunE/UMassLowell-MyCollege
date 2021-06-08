/***********************************************************
 Author: Erdun E
 Date: feb 21
 Effort: 3h
 Interface proposal: We created a container, and the next step is to put the function inside it
 ***********************************************************/
#include <stdlib.h>
#include "bit_flags.h"

struct bit_flags{
    int size;
    int capacity;
    unsigned int* data;
};

typedef struct bit_flags Bit_flags;


BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits){
    
    Bit_flags* pBit_flags;
    pBit_flags = malloc(sizeof(Bit_flags));
    
    
    if (pBit_flags != NULL)
    {
        pBit_flags -> capacity = 32;
        pBit_flags -> size = number_of_bits;
       
        while (number_of_bits >= pBit_flags->capacity){
            pBit_flags -> capacity += 32;
        }
        
        pBit_flags->data = (unsigned int*) malloc(sizeof(unsigned int)*pBit_flags -> capacity);
        
        
        if (pBit_flags == NULL){
            free(pBit_flags);
            pBit_flags = NULL;
        }
        for ( int i = 0; i < pBit_flags->size; i++){
            pBit_flags->data[i] = 0;
        }
    }
    return pBit_flags;
}


Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position){

    unsigned int* temp;
    Bit_flags* pBit_flags = (Bit_flags*) hBit_flags;
    while ((flag_position) >= pBit_flags -> capacity){
        temp = (unsigned int*)malloc(sizeof(unsigned int) * (pBit_flags -> capacity + 32));
        if (temp == NULL){
            return FAILURE;
        }
        for (int i = 0; i < pBit_flags -> size; i++){
            temp[i] = pBit_flags -> data[i];
        }
        
        free(pBit_flags -> data);
        pBit_flags -> data = temp;
        pBit_flags -> capacity += 32;
    }
    
    if (flag_position >= pBit_flags -> size){
        pBit_flags -> size = flag_position + 1;
    }
    pBit_flags -> data[flag_position / 32] |= (1 << (flag_position));
    
    
    return SUCCESS;
}


Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position)
{
    unsigned int* temp;
    Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
    while ((flag_position) >= pBit_flags->capacity){
        temp = (unsigned int*)malloc(sizeof(unsigned int) * (pBit_flags->capacity + 32));
        if (temp == NULL){
            
            return FAILURE;
        }
        for (int i = 0; i < pBit_flags->size; i++){
            temp[i] = pBit_flags->data[i];
        }
       
        
        free(pBit_flags->data);
        pBit_flags->data = temp;
        pBit_flags->capacity += 32;
    
    }
    
    
    if (flag_position >= pBit_flags->size){
        pBit_flags->size = flag_position + 1;
    }
    pBit_flags->data[flag_position / 32] &= ~(1 << (flag_position));
    
    return SUCCESS;
}


BIT_FLAGS bit_flags_init_default(void){
    Bit_flags* pBit_flags;
    pBit_flags = (Bit_flags*)malloc(sizeof(Bit_flags));
    if (pBit_flags != NULL){
        pBit_flags->size = 5;
        pBit_flags->capacity = 32;
        pBit_flags->data = (unsigned int*)malloc(sizeof(unsigned int)*pBit_flags->capacity);
        if (pBit_flags->data == NULL){
            free(pBit_flags);
            pBit_flags = NULL;
        }
    }
    return pBit_flags;
}


int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position){
    int bit = 0, bit_set = flag_position;
    Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
    
    if(flag_position < 0 || flag_position > pBit_flags->capacity)
        bit = -1;
    else
    {
        flag_position /= pBit_flags->capacity;
        if((pBit_flags->data[flag_position] >> bit_set) & 1)
        {
            bit = pBit_flags->data[flag_position];
        }
    }
    
    return bit;
}


int bit_flags_get_size(BIT_FLAGS hBit_flags)
{
    Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
    
    return pBit_flags->size;
}


int bit_flags_get_capacity(BIT_FLAGS hBit_flags)
{
    Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
    
    return pBit_flags->capacity;
}


void bit_flags_destroy(BIT_FLAGS* phBit_flags)
{
    Bit_flags* pBit_flags = (Bit_flags*) *phBit_flags;
    
    free(pBit_flags -> data);
    free(pBit_flags);
    
    *phBit_flags = NULL;
}

