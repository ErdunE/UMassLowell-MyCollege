#include <stdio.h>

void smileface()
{
    printf("  ****\n * . .*\n*      *\n*  \\_/ *\n *    *\n  ****\n\n");
}

int main(){
    int a,i;
    printf("How many face do you want: \n");
    scanf("%d",&a);
    for((i = 0);i<a;i++)
    {
        smileface();
    }
}

