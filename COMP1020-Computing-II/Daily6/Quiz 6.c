/***********************************************************
 Author: Erdun E
 Date: Feb 11
 Effort: 2 hours
 Purpose: practice more with the bit wise operators and shifts
 ***********************************************************/
#include<stdio.h>
void set_flag(unsigned int flag_holder[], int flag_position);
void unset_flag(unsigned int flag_holder[], int flag_position);
int check_flag(unsigned int flag_holder[], int flag_position);
void display_32_flags_as_array(unsigned int flag_holder);
void display_flags(unsigned int flag_holder[], int size);

int main(int argc, char* argv[])
{
    unsigned int flag_holder[5] = { 0 };
    set_flag(flag_holder, 3);
    set_flag(flag_holder, 16);
    set_flag(flag_holder, 31);
    set_flag(flag_holder, 87);
    display_flags(flag_holder, 5);
    printf("\n\n");
    unset_flag(flag_holder, 31);
    unset_flag(flag_holder, 3);
    set_flag(flag_holder, 99);
    set_flag(flag_holder, 100);
    display_flags(flag_holder, 5);
    return 0;
}


void set_flag(unsigned int flag_holder[], int flag_position){
    int bit_need_to_set = flag_position;
    flag_position /= 32;
    flag_holder[flag_position] |= 1 << (bit_need_to_set%32);
}
void unset_flag(unsigned int flag_holder[], int flag_position){
    int bit_need_to_set = flag_position;
    flag_position /= 32;
    flag_holder[flag_position] &= ~(1 << (bit_need_to_set%32));
}
int check_flag(unsigned int flag_holder[], int flag_position){
    int bit;
    int bit_need_to_set = flag_position;
    flag_position /= 32;
    if((flag_holder[flag_position] >> bit_need_to_set) & 1)
        bit = 1;
    else
        bit = 0;
    return bit;
}
void display_32_flags_as_array(unsigned int flag_holder){
    int n = 0;
    while(n <= 31){
        printf("%d", check_flag(&flag_holder, n));
        n++;
        if(n%4 == 0)
            printf(" ");
    }
    printf("\n");
}
void display_flags(unsigned int flag_holder[], int size){
    for(int i = 0; i < size; i++)
        display_32_flags_as_array(flag_holder[i]);
}
