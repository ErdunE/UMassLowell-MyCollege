#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[])
{
	MY_STRING hMy_string = NULL;
	MY_STRING hLeft_string = NULL;
	MY_STRING hRight_string = NULL;

	hMy_string = my_string_init_default();
	hMy_string = my_string_init_c_string("hello");
	printf("The size is %d\n", my_string_get_size(hMy_string));
	printf("The capacity is %d\n", my_string_get_capacity(hMy_string));
	hLeft_string = my_string_init_c_string("umass");
	hRight_string = my_string_init_c_string("umass lowell");
	printf("The number is %d\n", my_string_compare(hLeft_string, hRight_string));

	my_string_destroy(&hMy_string);
	my_string_destroy(&hLeft_string);
	my_string_destroy(&hRight_string);

	return 0;
}
