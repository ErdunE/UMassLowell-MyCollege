/***********************************************
 Author: Erdun E
 Date: 03-02-2018
 Answer to question: When I typed 50,000, it worked. Their difference is that this function can use smaller amounts of memory.
 ***********************************************/

#include <stdio.h>

void loop_down_to_zero(int n)
{
    int i;
    for(i=n;i>=0;i--)
    {
        printf("%d\n",i);
    }
}

void loop_up_to_int(int n)
{
    int i;
    for(i=0;i<=n;i++)
    {
        printf("%d\n",i);
    }
}

int main(void)
{
    int n,r;
    
    printf("Please enter a positive number: ");
    r=scanf("%d",&n);
    while(n<0)
    {
        printf("Please enter a positive number: ");
        r=scanf("%d",&n);
    }
    
    loop_down_to_zero(n);
    printf("****\n");
    loop_up_to_int(n);
    

}

