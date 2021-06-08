#include <stdio.h>
#include <stdlib.h>
int main (int argc, char* argv[])
{
    int **pointer;
    int i,j;
    pointer=(int**) malloc(sizeof(int*)*20);
    for (i=0;i<20;i++)
        pointer[i]=(int*) malloc(sizeof(int)*30);
    for(i=0;i<20;i++)
    {
        for(j=0;j<30;j++)
        pointer[i][j]=i+j;
    }
    printf("Hello world! I have created a dynamic 2D-array\n");
    for(i=0;i<20;i++)
    {
        for (j=0;j<30;j++)
        printf("%3d",pointer[i][j]);
        printf("\n");
    }
    free(*pointer);
    
    
    
    return 0;
}

