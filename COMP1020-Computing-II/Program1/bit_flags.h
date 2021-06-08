//
//  bit_flags.h
//  Program 1
//
//  Created by 额尔敦 on 2/21/19.
//  Copyright © 2019 额尔敦. All rights reserved.
//

#ifndef bit_flags_h
#define bit_flags_h
#include "status.h"

typedef void* BIT_FLAGS;

BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits);

Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position);
Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position);

int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position);
int bit_flags_get_size(BIT_FLAGS hBit_flags);
int bit_flags_get_capacity(BIT_FLAGS hBit_flags);

void bit_flags_destroy(BIT_FLAGS* phBit_flags);

#endif /* bit_flags_h */
