/**********************************************************************
 Program: Freey Loading IV
 Author: Erdun E
 Date: 03-15-2019
 Time spent: 1 day
 Purpose: determine the amount of times that a ferry must cross a river in order to transport all the cars from one side to the other.
 ***********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[])
{
    int c,l,m, *crossing_temp, *Length_of_car, temp;
    char **await_the_ferry;
    char ferrySide[7]="left";
    
    scanf("%d", &c);
    
    crossing_temp=(int *)malloc(sizeof(int) * c);
    
    for(int i=0;i<c;i++)
        crossing_temp[i]=0;
    
    for(int i=0;i<c;i++)
    {
        crossing_temp[i]=1;
        scanf("%d %d", &l, &m);
        
        l *= 100;
        
        Length_of_car=(int*)malloc(sizeof(int) * m);
        await_the_ferry=(char **) malloc(sizeof(char *) * m);
        
        for(int j=0;j<m;j++)
        {
            await_the_ferry[j]=(char *)malloc(sizeof(char) * 7);
            scanf("%d %s", &Length_of_car[j],await_the_ferry[j]);
        }
        
        temp=l;
        strcpy(ferrySide,"left");
        
        for(int j=0;j<m;)
        {
            if(Length_of_car[j] < temp && strcmp(ferrySide,await_the_ferry[j])==0)
            {
                temp=temp-Length_of_car[j];
                j++;
            }
            else
            {
                crossing_temp[i]++;
                
                if(strcmp(ferrySide,"left") == 0)
                    strcpy(ferrySide,"right");
                else
                    strcpy(ferrySide,"left");
                
                temp=l;
            }
        }
        
        free(Length_of_car);
        free(await_the_ferry);
    }
    
    for(int i=0;i<c;i++)
    {
        printf("%d\n",crossing_temp[i]);
    }
    
    return 0;
}
