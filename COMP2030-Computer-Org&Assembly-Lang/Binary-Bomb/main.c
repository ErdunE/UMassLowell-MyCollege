
#include <stdio.h>
#include <stdlib.h>

static int func4(int a, int b, int c)
{
    int tmp = ((((c - b) + ((c - b) >> 31 )) >> 1 ) + b ) ;
    
    if (tmp <= a)
    {
        if (tmp == a)
        {
            return (0);
        }
        else
        {
            return func4(a, tmp + 1 , c) * 2 + 1;
        }
    }
    else
    {
        return func4(a, b, tmp - 1 ) * 2;
    }
    
}


int main(int argc, const char *argv[])
{
    int i, result;
 
    for (i = 0; i < 14; ++i) {
        result = func4(i, 0, 14);
        if (result == 3) {
            printf("%d\n", i);
        }
    }
    return 0;
}


/*void phase_4(const char *input)
{
    //  0x8(%rsp)  0xc(%rsp)
    int num1, num2;
 
    //                     %rdi    %rsi   %rdx   %rcx
    int result = sscanf(input, "%d %d", &num1, &num2);
    if (result != 2) {
        explode_bomb();
    }
 
    if (num1 > 0xe) {
        explode_bomb();
    }
    
    //   %edi  %esi %edx
    result = func4(num1, 0, 0xe);
    if (result != 3) {
        explode_bomb();
    }
 
    if (num2 != 3) {
        explode_bomb();
    }
}
 */

