
#include <stdio.h>
enum status{FAILURE, SUCCESS};
enum boolean{FALSE,TRUE};
struct string
{
	int size;
	int capacity;
	char* ch;
};
typedef enum status Status;
typedef enum boolean Boolean;
typedef struct string String;

typedef void* MY_STRING;

MY_STRING my_string_init_default(void);

MY_STRING my_string_init_c_string(const char* str);

int my_string_get_size(MY_STRING hMy_string);

int my_string_get_capacity(MY_STRING hMy_string);

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string);

void my_string_destroy(MY_STRING* phMy_string);

Status my_string_extraction(MY_STRING hMy_string, FILE* fp);
Status my_string_insertion(MY_STRING hMy_string, FILE* fp);

Status my_string_push_back(MY_STRING hMy_string, char item);
Status my_string_pop_back(MY_STRING hMy_string);
char* my_string_at(MY_STRING hMy_string, int index);
char* my_string_c_str(MY_STRING hMy_string);

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend);
Boolean my_string_empty(MY_STRING hMy_string);
