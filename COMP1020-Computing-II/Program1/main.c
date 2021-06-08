//
//  main.c
//  Program 1
//
//  Created by 额尔敦 on 2/21/19.
//  Copyright © 2019 额尔敦. All rights reserved.
//

#include <stdio.h>
#include "bit_flags.h"

int main(int argc, char* argv[])
{
    int userInput;
    BIT_FLAGS count;
    
    printf("Enter the bit stream length to be? ");
    scanf("%d", &userInput);
    
    count = bit_flags_init_number_of_bits(userInput);
    
    printf("Bit flags set: %d %d %d\n",
           bit_flags_set_flag(count, 3),
           bit_flags_set_flag(count, 5),
           bit_flags_set_flag(count, 0));
    printf("Bit flags size: %d\n",
           bit_flags_get_size(count));
    printf("Bit flags capacity: %d\n",
           bit_flags_get_capacity(count));
    printf("Bit flags check: %d %d\n\n",
           bit_flags_check_flag(count, 3),
           bit_flags_check_flag(count, 0));
    
    printf("Bit flags clear: %d %d %d\n",
           bit_flags_unset_flag(count, 3),
           bit_flags_unset_flag(count, 10),
           bit_flags_unset_flag(count, 5));
    printf("Bit flags size: %d\n",
           bit_flags_get_size(count));
    printf("Bit flags capacity: %d\n",
           bit_flags_get_capacity(count));
    printf("Bit flags check: %d %d\n\n",
           bit_flags_check_flag(count, 3),
           bit_flags_check_flag(count, 0));
    
    bit_flags_destroy(&count);
    
    return 0;
}
