/**********************************************************************
 Program: Program 3 Number Filter
 Author: Erdun E
 Date: April 17
 Time spent: almost 1 day
 Purpose: Take a large number of integer input, and first filter similar Numbers, remove all duplicate values and then sort, output results.
 ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

struct array
{
    int size;
    int capacity;
    int* data;
};

typedef struct array Array;
typedef void* ARRAY;
ARRAY init_array_number(void);
void insert_to_array(ARRAY hTemp_array, int item);
void fliter_array(ARRAY hTemp_array);
void destroy_array(ARRAY* phTemp_array);
int get_size(ARRAY hTemp_array);
int get_capacity(ARRAY hTemp_array);
int* item_at(ARRAY hTemp_array, int index);
void swop(int* a, int* b);
void buble_sort(ARRAY hTemp_array, int size);

int main()
{
    FILE* fp;
    ARRAY hmy_array=NULL;
    int size_temp;
    int temp = 1;
    hmy_array = init_array_number();
    fp = stdin;
    do {
        fscanf(fp, "%d", &temp);
        if (temp != -1 && temp >= 0 && temp <= 2000000000){
            insert_to_array(hmy_array,temp);
        }
    } while (temp != -1);
    
    fliter_array(hmy_array);
    size_temp = get_size(hmy_array);
    buble_sort(hmy_array, size_temp);
    for (int i = 0; i < get_size(hmy_array); i++){
        printf("%d\n", *item_at(hmy_array,i));
    }
    destroy_array(&hmy_array);
    return 0;
}

ARRAY init_array_number(void){
    Array* pTemp_array;
    pTemp_array = (Array*)malloc(sizeof(Array));
    if (pTemp_array != NULL){
        pTemp_array->size = 0;
        pTemp_array->capacity = 8;
        pTemp_array->data = (int*)malloc(sizeof(int)*pTemp_array->capacity);
        if (pTemp_array->data == NULL){
            free(pTemp_array);
            pTemp_array = NULL;
        }
    }
    return pTemp_array;
}

void insert_to_array(ARRAY hTemp_array, int item){
    Array* pTemp_array = (Array*)hTemp_array;
    int* temp;
    if (pTemp_array->size >= pTemp_array->capacity){
        temp = (int*)malloc(sizeof(int) * 2 * pTemp_array->capacity);
        if (temp == NULL){
            exit(1);
        }
        for (int i = 0; i < pTemp_array->size; i++){
            temp[i] = pTemp_array->data[i];
        }
        free(pTemp_array->data);
        pTemp_array->data = temp;
        pTemp_array->capacity *= 2;
    }
    pTemp_array->data[pTemp_array->size] = item;
    pTemp_array->size++;
}

void fliter_array(ARRAY hTemp_array)
{
    Array* pTemp_array = (Array*)hTemp_array;
    int* temp;
    int* result;;
    int flag;
    int count=0;
    temp = (int*)malloc(sizeof(int) * pTemp_array->capacity);
    temp[count] = pTemp_array->data[0];
    count++;
    int size_temp;
    size_temp = pTemp_array->size;
    for (int i = 1; i < size_temp; i++){
        flag = 0;
        for (int j = 0; j < count; j++){
            if (pTemp_array->data[i] == temp[j]){
                flag = 1;
                pTemp_array->size--;
                pTemp_array->capacity--;
                break;
            }
        }
        if (flag == 1)
            continue;
        temp[count] = pTemp_array->data[i];
        count++;
    }
    free(pTemp_array->data);
    result = (int*)malloc(sizeof(int) * pTemp_array->capacity);
    for (int k = 0; k < pTemp_array->size; k++){
        result[k] = temp[k];
    }
    pTemp_array->data = result;
}

void swop(int* a, int* b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void buble_sort(ARRAY hTemp_array, int size) {
    Array* pTemp_array = (Array*)hTemp_array;
    int swopped = 1, i = 1;
    for (int n = 0; n < size - 1 && swopped; i++) {
        swopped = 0;
        for (i = 0; i < size - 1; i++) {
            if (pTemp_array->data[i] > pTemp_array->data[i + 1]) {
                swop(&pTemp_array->data[i], &pTemp_array->data[i + 1]);
                swopped = 1;
            }
        }
    }
}

void destroy_array(ARRAY* phTemp_array){
    Array* pTemp_array = (Array*)*phTemp_array;
    free(pTemp_array->data);
    free(pTemp_array);
    *phTemp_array = NULL;
}

int get_size(ARRAY hTemp_array){
    Array* pTemp_array = (Array*)hTemp_array;
    return pTemp_array->size;
}

int get_capacity(ARRAY hTemp_array){
    Array* pTemp_array = (Array*)hTemp_array;
    return pTemp_array->capacity;
}

int* item_at(ARRAY hTemp_array, int index){
    Array* pTemp_array = (Array*)hTemp_array;
    if (index < 0 || index >= pTemp_array->size)
    {
        return NULL;
    }
    return &pTemp_array->data[index];
}

