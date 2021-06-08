
#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#define SIZE 100
int main(int argc, char* argv[])
{
	/*MY_STRING hMy_string = NULL;
	FILE* fp;
	hMy_string = my_string_init_default();
	//fp = fopen("simple.txt", "r");
	fp = fopen("dictionary.txt", "r");
	while(my_string_extraction(hMy_string, fp))
	{
		//my_string_insertion(hMy_string, stdout);
		//printf("\n");
		//if(fgetc(fp)== ' ')
		//{
			//printf("Found a space after the string\n");
		//}
		if((my_string_get_size(hMy_string))==29)
		{
			my_string_insertion(hMy_string, stdout);
			printf("\n");
		}
	}
	my_string_destroy(&hMy_string);
	fclose(fp);
	return 0;*/
	
	int i;
	MY_STRING hMy_string[SIZE];
	hMy_string[0] = my_string_init_c_string("COPY ME!");
	for (i=1;i<SIZE;i++)
	{
		hMy_string[i]=my_string_init_default();
	}
	for(i=1;i<SIZE;i++)
	{
		my_string_assignment(&hMy_string[i],hMy_string[0]);
	}
	for(i=0;i<SIZE;i++)
	{
		my_string_insertion(hMy_string[i],stdout);
		printf("\n");
		my_string_destroy(&hMy_string[i]);
	}
	return 0;
}


