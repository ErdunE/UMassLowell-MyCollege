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
	String* pstr1 = (String*)hLeft_string;
	String* pstr2 = (String*)hRight_string;
	int i = 0;
	while (pstr1->data[i] != '\0' && pstr2->data[i] != '\0')
	{


		if (pstr1->data[i] > pstr2->data[i])
		{
			return 1;
		}
		else if (pstr1->data[i] < pstr2->data[i])
		{
			return -1;
		}
		else if (pstr1->data[i] == pstr2->data[i])
		{
		i++;
		}
	}
	if (pstr1->size > pstr2->size)
	{
		return 1;
	}
	else if (pstr1->size < pstr2->size)
	{
		return -1;
	}
	else if (pstr1->size == pstr2->size)
	{
		return 0;
	}
	return 99;
}

void my_string_destroy(Item* pItem)
{
	String* pString = (String*)* pItem;
	free(pString->data);
	free(pString);
	*pItem = NULL;
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
	String* pString = (String*)hMy_string;
	char ch;
	char* temp;
	int i = 0, j = 0;
	pString->size = 0;


	ch = fgetc(fp);
	while (ch != EOF && ch != ' ' && ch != '\n')
	{
		if (pString->size >= pString->capacity)
		{
			temp = malloc(sizeof(char) * 2 * pString->capacity);
			if (temp == NULL)
			{
				return FAILURE;
			}
			for (j = 0; j < pString->size; j++)
			{
				temp[j] = pString->data[j];
			}
			free(pString->data);

			pString->data = temp;
			pString->capacity *= 2;
		}


	pString->data[i] = ch;
	i++;
	pString->size++;
	ch = fgetc(fp);
	}


	if (ch == ' ')
	{
		if (i != 0)
		{
		ungetc(ch, fp);
		}
	}

	if (pString->size == 0)
	{
		return FAILURE;
	}


	return SUCCESS;
	}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
	String* pString = (String*)hMy_string;
	int i = 0;
	if (pString->size == 0)
	{
		return FAILURE;
	}
	while (i < pString->size)
	{
		fputc(pString->data[i], fp);
		i++;
	}
	return SUCCESS;
}

Status my_string_push_back(MY_STRING hMy_string, char item)
{
	String* pString = (String*)hMy_string;


	char* temp;
	int i;


	if (pString->size + 1 >= pString->capacity)
	{
		temp = (char*)malloc(sizeof(char) * 2 * pString->capacity);
		if (temp == NULL)
		{
			return FAILURE;
		}
		for (i = 0; i < pString->size; i++)
		{
			temp[i] = pString->data[i];
		}
		free(pString->data);
		pString->data = temp;
		pString->capacity *= 2;
	}

	pString->data[pString->size] = item;
	pString->size++;
	pString->data[pString->size] = '\0';
	//printf("===> %s\n", pString->data);
	return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string)
{
	String* pString = (String*)hMy_string;


	if (my_string_empty(hMy_string))
	{
		return FAILURE;
	}
	pString->size--;
	pString->data[pString->size] = '\0';


	return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index)
{
	String* pString = (String*)hMy_string;


	if (index < 0 || index >= pString->size)
	{
		return NULL;
	}
	return &pString->data[index];
}

char* my_string_c_str(MY_STRING hMy_string)
{
	String* pString = (String*)hMy_string;
	//pString->data[pString->size] = '\0';
	return &pString->data[0];
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
	//String* pStr1 = (String*)hResult;
	String* pStr2 = (String*)hAppend;
	int i;
	for (i = 0; i < pStr2->size; i++)
	{
		my_string_push_back(hResult, pStr2->data[i]);
	}

	return SUCCESS;
}

Boolean my_string_empty(MY_STRING hMy_string)
{
	String* pString = (String*)hMy_string;
	if (pString->size == 0)
	{
		return TRUE;
	}
	return FALSE;
}

void my_string_assignment(Item* phLeft, Item Right)
{
	String* pLeft = (String*)*phLeft;
	if (pLeft == NULL)
	{
		pLeft = (String*)malloc(sizeof(String));
		if (pLeft == NULL)
		{
			printf("Failed to mallocate space\n");
			exit(1);
		}
		*phLeft = pLeft;
	}
	my_string_concat(*phLeft, Right);
}
