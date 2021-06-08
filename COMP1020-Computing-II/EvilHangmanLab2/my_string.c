#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

MY_STRING my_string_init_default(void)
{
	String* pString;
	pString = (String*)malloc(sizeof(String));
	if (pString != NULL)
	{
		pString->size = 0;
		pString->capacity = 7;
		pString->data = (char*)malloc(sizeof(char) * pString->capacity);
		if (pString->data == NULL)
		{
			free(pString);
			pString = NULL;
		}
	}
	return pString;
}

MY_STRING my_string_init_c_string(const char* c_string)
{
	int i;
	for (i = 0; c_string[i] != '\0'; i++);
	String* pString;
	pString = (String*)malloc(sizeof(String));
	if (pString != NULL)
	{
		pString->size = i;
		pString->capacity = i + 1;
		pString->data = (char*)malloc(sizeof(char) * pString->capacity);
		if (pString->data != NULL)
		{
			for (i = 0; c_string[i] != '\0'; i++)
			{
				pString->data[i] = c_string[i];
			}
			pString->data[i] = '\0';
		}
	}
	return pString;
}

int my_string_get_size(MY_STRING hMy_string)
{
	String* pString = (String*)hMy_string;
	return pString->size;
}

int my_string_get_capacity(MY_STRING hMy_string)
{
	String* pString = (String*)hMy_string;
	return pString->capacity;
}
	
int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
	String* str1 = (String*)hLeft_string;
	String* str2 = (String*)hRight_string;
	int i = 0;
	while (str1->data[i] != '\0' || str2->data[i] != '\0')
	{
		
		if (str1->data[i] > str2->data[i])
		{
			return 1;
		}
		else if (str1->data[i] < str2->data[i])
		{
			return -1;
		}
		else if (str1->data[i] == str2->data[i])
		{
			i++;
		}
	}
	if (str1->size > str2->size)
	{
		return 2;
	}
	else if (str1->size < str2->size)
	{
		return -2;
	}
	else if (str1->size == str2->size)
	{
		return 0;
	}
	return 1;
}

void my_string_destroy(MY_STRING* phMy_string)
{
	String* pString = (String*)* phMy_string;
	free(pString->data);
	free(pString);
	*phMy_string = NULL;
}
