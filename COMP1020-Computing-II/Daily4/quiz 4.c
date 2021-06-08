/***********************************************************
 Author: Erdun E
 Date: Feb 7 2019
 Effort: 2.5 hours
 ***********************************************************/
#include <stdio.h>
void set_flag(unsigned int *flag_holder, int flag_position);
void unset_flag(unsigned int *flag_holder, int flag_position);
int check_flag(unsigned int flag_holder, int flag_position);
void display_32_flags(unsigned int flag_holder);
void display_flags(unsigned int flag_holder[], int size);


int main(int argc, char* argv[]){
    
    unsigned int flag_holder = 0;
    
    set_flag(&flag_holder, 3);
    set_flag(&flag_holder, 16);
    set_flag(&flag_holder, 31);
    display_32_flags(flag_holder);
    
    unset_flag(&flag_holder, 31);
    unset_flag(&flag_holder, 3);
    set_flag(&flag_holder, 9);
    display_32_flags(flag_holder);
    
    return 0;
}
void set_flag(unsigned int *flag_holder, int flag_position){
    int n = 1 << flag_position;
    *flag_holder = *flag_holder | n;
}

int check_flag(unsigned int flag_holder, int flag_position){
    int n = 1 << flag_position;
    int bit = flag_holder & n;
    if(bit == 0)
        return 0;
    else
        return 1;
}

void unset_flag(unsigned int * flag_holder, int flag_position){
    int bit_need_to_set = flag_position;
    flag_position /= 32;
    flag_holder[flag_position] &= ~(1 << (bit_need_to_set%32));
}

void display_32_flags(unsigned int flag_holder){
    for(int x=31; x>=0; x--){
        printf("%d", check_flag(flag_holder, x));
        if(x%4 == 0){
            printf(" ");
        }
    }
    printf("\n");
}
