#include <string.h>
#include "my_string.h"
Status test_init_default_returns_nonNULL(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	if(hString == NULL)
	{
		my_string_destroy(&hString);
		strncpy(buffer, "test_init_default_returns_nonNULL\n" "my_string_init_default retuns NULL", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy(&hString);
		strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
		return SUCCESS;
	}
}

Status test_get_size_on_init_default_returns_0(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();
	if(my_string_get_size(hString)!=0)
	{
		status = FAILURE;
		printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n" "Did not receive 0 from get_size after init_default\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n", length);
	}
	my_string_destroy(&hString);
	return status;
}
Status test_my_string_get_size_return_0(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();
	if(my_string_get_size(hString)!=0)
	{
		status = FAILURE;
		strncpy(buffer, "test_get_size_on_init_default_return_0\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_get_size_on_init", length);
	}
	my_string_destroy(&hString);
	return status;
}
Status test_my_string_init_c_string_returns_NULL(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("Computer");
	if(hString == NULL)
	{
		my_string_destroy(&hString);
		strncpy(buffer, "test_MY_STRING my_string_init_c_string_returns_NULL\n" "my_string_init_c_string returns NULL", length);

		return FAILURE;
	}
	else
	{
		my_string_destroy(&hString);
		strncpy(buffer, "\ttest_MY_STRING my_string_init_c_string_returns_NULL\n", length);

		return SUCCESS;
	}


}

Status test_my_string_get_capacity_returns_0(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();
	if(my_string_get_capacity(hString)!=7)
	{
		status = FAILURE;
		strncpy(buffer, "test_my_string_get_capacity_returns_0\n" "my_string_get_capacity returns 0", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "\ttest_my_string_get_capacity_returns_0\n", length);
		
	}
	my_string_destroy(&hString);
	return status;
}
	
Status test_my_string_compare_returns_0(char* buffer, int length)
{
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	Status status;
	hString1 = my_string_init_c_string("Comp");
	hString2 = my_string_init_c_string("Computer");
	if(my_string_compare(hString1 , hString2) == -1)
	{
		status = SUCCESS;
		strncpy(buffer, "test_my_string_compare_returns_0\n" "my_string_compare returns 0", length);
	}
	else
	{
		status= FAILURE;
		strncpy(buffer, "\ttest_my_string_compare_returns_0\n",length);
	}
	my_string_destroy(&hString1);
	my_string_destroy(&hString2);
	return status;
}

Status test_my_string_extraction_returns_SUCCESS(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	FILE *fp;
	hString = my_string_init_default();
	fp=fopen("simple.txt", "r");
	if(my_string_extraction(hString, fp) ==FAILURE)
	{
		status=FAILURE;
		strncpy(buffer, "test_my_string_extraction_returns_SUCCESS\n" "my_string_extraction returns SUCCESS", length);
		
	}
	else
	{
		status=SUCCESS;
		strncpy(buffer, "\ttest_my_string_extraction_returns_SUCCESS\n", length);
		
	}
	my_string_destroy(&hString);
	fclose(fp);
	return status;
}
Status test_my_string_insertion_returns_SUCCESS(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	FILE * fp;
	hString = my_string_init_default();
	fp=fopen("simple.txt","r");
	if(my_string_extraction(hString, fp))
	{
		if(my_string_insertion(hString,fp))
		{
			status=SUCCESS;
			strncpy(buffer, "test_my_string_insertion_returns_SUCCESS\n" "my_string_insertion returns SUCCESS", length);	
		}
		else
		{
			status= FAILURE;
			strncpy(buffer, "\ttest_my_string_insertion_returns_SUCCESS\n", length);	
		}
	}
	else
	{
		status=FAILURE;
		printf("fail");
	}
	my_string_destroy(&hString);
	fclose(fp);
	return status;
}
Status test_my_string_push_back_returns_SUCCESS(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();
	if(my_string_push_back(hString, 'a'))
	{
		status = SUCCESS;
		strncpy(buffer, "test_my_string_push_back_returns_SUCCESS\n" "my_string_push_back returns SUCCESS", length);
	}
	else
	{
		status = FAILURE;
		strncpy(buffer, "\ttest_my_string_push_back_returns_SUCCESS\n", length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_my_string_pop_back_returns_SUCCESS(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("abcdef");
	if(my_string_pop_back(hString))
	{
		status= SUCCESS;
		strncpy(buffer, "test_my_string_pop_back_returns_SUCCESS\n" "my_string_pop_back returns SUCCESS", length);
	}
	else
	{
		status= FAILURE;
		strncpy(buffer, "\ttest_my_string_pop_back_returns_SUCCESS\n", length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_my_string_at_returns_c(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("abcde");
	if(my_string_at(hString, 0)==NULL)
	{
		status= FAILURE;
		strncpy(buffer, "test_my_string_at_returns_c\n" "my_string_at returns SUCCESS", length);
	}
	else
	{
		status= SUCCESS;
		strncpy(buffer, "\ttest_my_string_at_returns_c\n", length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_my_string_c_str_returns_c(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("Computer");
	if(my_string_c_str(hString)==NULL)
	{
		status= FAILURE;
		strncpy(buffer, "test_my_string_c_str_returns_c\n" "my_string_c_str returns SUCCESS", length);
	}
	else
	{
		status= SUCCESS;
		strncpy(buffer, "\ttest_my_string_c_str_returns_c\n", length);
	}
	my_string_destroy(&hString);
	return status;	
	
}
Status test_my_string_concat_returns_0(char* buffer, int length)
{
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	Status status;
	hString1 = my_string_init_c_string("abcd");
	hString2 = my_string_init_c_string("efgh");
	if(my_string_concat(hString1, hString2))
	{
		status= SUCCESS;
		strncpy(buffer, "test_my_string_concat_returns_0\n" "my_string_concat returns 0", length);
	}
	else
	{
		status= FAILURE;
		strncpy(buffer, "\ttest_my_string_concat_returns_0\n", length);
	}
	my_string_destroy(&hString1);
	my_string_destroy(&hString2);
	return status;

}
Status test_my_string_empty_returns_SUCCESS(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("Computer");
	if(!my_string_empty(hString))
	{
		status= SUCCESS;
		strncpy(buffer, "test_my_string_empty_returns_SUCCESS\n" "my_string_empty returns SUCCESS", length);
	}
	else
	{
		status= FAILURE;
		strncpy(buffer, "\ttest_my_string_empty_returns_SUCCESS\n", length);
	}
	my_string_destroy(&hString);
	return status;
	
}
Status test_my_string_destroy_returns_SUCCESS(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	my_string_destroy(&hString);
	if(hString==NULL)
	{
		strncpy(buffer, "test_my_string_destroy_returns_SUCCESS\n" "my_string_destroy returns SUCCESS", length);
		return SUCCESS;
	}
	else
	{
		strncpy(buffer, "\ttest_my_string_destroy_returns_SUCCESS\n", length);
		return FAILURE;
	}
}
