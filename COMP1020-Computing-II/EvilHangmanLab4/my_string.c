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
		pString->ch = (char*)malloc(sizeof(char) * pString->capacity);
		if (pString->ch == NULL)
		{
			free(pString);
			pString = NULL;
		}
	}
	return pString;
}

MY_STRING my_string_init_c_string(const char* str)
{
	int i;
	for (i = 0; str[i] != '\0'; i++);
	String* pString;
	pString = (String*)malloc(sizeof(String));
	if (pString != NULL)
	{
		pString->size = i;
		pString->capacity = i + 1;
		pString->ch = (char*)malloc(sizeof(char) * pString->capacity);
		if (pString->ch != NULL)
		{
			for (i = 0; str[i] != '\0'; i++)
			{
				pString->ch[i] = str[i];
			}
			pString->ch[i] = '\0';
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
	while (str1->ch[i] != '\0' || str2->ch[i] != '\0')
	{
		
		if (str1->ch[i] > str2->ch[i])
		{
			return 1;
		}
		else if (str1->ch[i] < str2->ch[i])
		{
			return -1;
		}
		else if (str1->ch[i] == str2->ch[i])
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
	return 99;
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
	String* pString = (String*)hMy_string;
	char c;
	char* temp;
	int i = 0, j = 0;
	pString->size = 0;
	c = fgetc(fp);
	while (c != EOF && c != ' ' && c != '\n')
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
				temp[j] = pString->ch[j];
			}
			free(pString->ch);

			pString->ch = temp;
			pString->capacity *= 2;
		}		
		pString->ch[i] = c;
		i++;
		pString->size++;
		c = fgetc(fp);
	}	
	if (c == ' ')
	{
		if (i != 0)
		{
			ungetc(c, fp);
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
		fputc(pString->ch[i], fp);
		i++;
	}
	return SUCCESS;
}
Status my_string_push_back(MY_STRING hMy_string, char item)
{
	String* pString = (String*)hMy_string; //cast to known type
	int* temp;
	int i;
	//is there enough room?
	//if not - make room (resize)
	if (pString->size>= pString->capacity) {
		temp = malloc(sizeof(int)*2*pString->capacity);
		if (temp == NULL)
		{
			return FAILURE;
		}
		for (i = 0; i < pString->size; i++) {
			temp[i] = pString->ch[i];
		}	
		free(pString->ch);
		 
		pString->capacity *= 2;
	}

	//YES -put at the available index (size)
	pString->ch[pString->size] = item;
	pString->size++;

	return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string)
{
	String* pString = (String*)hMy_string;
	if (pString->size <= 0)
	{
		return FAILURE;
	}
	pString->size--;
	return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index)
{
	String* pString = (String*)hMy_string;
	if (index < 0 || index >= pString->size)
	{
		return NULL;
	}
	return &pString->ch[index];
}

char* my_string_c_str(MY_STRING hMy_string)
{

	String* pString=(String*)hMy_string;
	pString->ch[pString->size]='\0';
	return pString->ch;
}
Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
	String* str1=(String*)hResult;
	String* str2=(String*)hAppend;
	int i;
	char* temp;
	if(str2->size==0)
	{return FAILURE;}
	else if(str1->size==0)
	{	for(i=0;i<str2->size;i++)
			{str1->ch[i]=str2->ch[i];}
		str1->size=str2->size;
		str1->capacity=str1->size+1;

	}
	else
	{
	int temp_size=str1->size+str2->size+1;
	int temp_capacity=temp_size +1;
	int j;
	temp=(char*)malloc(sizeof(char)*temp_capacity);
	if(temp!=NULL)
	{
		for(i=0; i <str1->size; i++)
		{temp[i]=str1->ch[i];}
		temp[i] =' ';
		j=str1->size+1;
		for(i=0;i<str2->size;i++)
		{temp[j+i]=str2->ch[i];}
		temp[j+i]='\0';
		free(str1->ch);
		str1->ch=temp;
		str1->capacity=temp_capacity;
		str1->size=temp_size;
	}
	}return SUCCESS;	
	/*for(i=0; str1[i]!='\0';i++);
	for(j=0; str2[i]!='\0';i++,j++)
	{
		str1[i]=str2[j];
	}
	str1[i]='\0';*/

}
Boolean my_string_empty(MY_STRING hMy_string)
{
	String* pString=(String*)hMy_string;
	if (pString->size==0)
	{return TRUE;}
	else
	{return FALSE;}
}
void my_string_destroy(MY_STRING* phMy_string)
{
	String* pString = (String*)* phMy_string;
	free(pString->ch);
	free(pString);
	*phMy_string = NULL;
}
