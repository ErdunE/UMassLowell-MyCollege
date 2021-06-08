#include<stdio.h>
#include"unit_test.h"

//Status long_function_name(char* buffer, int length);
int main(int argc, char* argv[])
{
	Status (*tests[])(char*,int)=
	{
		test_init_default_returns_nonNULL,
		test_get_size_on_init_default_returns_0,
		test_my_string_init_c_string_returns_NULL,
		test_my_string_get_capacity_returns_0,
		test_my_string_get_size_return_0,
		test_my_string_compare_returns_0,
		test_my_string_extraction_returns_SUCCESS,
		test_my_string_insertion_returns_SUCCESS,
		test_my_string_push_back_returns_SUCCESS,
		test_my_string_pop_back_returns_SUCCESS,
		test_my_string_at_returns_c,
		test_my_string_c_str_returns_c,
		test_my_string_concat_returns_0,
		test_my_string_empty_returns_SUCCESS,
		test_my_string_destroy_returns_SUCCESS
		
	};
	int number_of_functions=sizeof(tests)/sizeof(tests[0]);
	int i;
	char buffer[500];
	int success_count=0;
	int failure_count=0;

	for(i=0; i<number_of_functions; i++)
	{
		if(tests[i](buffer,500)==FAILURE)
		{
			printf("FAILED: Test %d failed muserably\n", i);
			printf("\t %s\n", buffer);
			failure_count++;
		}
		else
		{
			success_count++;
		}
	}
	printf("Total number of tests: %d\n", number_of_functions);
	printf("%d/%d Pass, %d/%d Failure\n", success_count, number_of_functions, failure_count, number_of_functions);
	return 0;
}
