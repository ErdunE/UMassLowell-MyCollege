/**********************************************************************
 Program: <reverse a linked list>
 Author: <Erdun E>
 Date: <02-14-2019>
 Time spent: <3 hours>
 Purpose: The purpose of this program is to reverse a linked list.
 ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

struct node;
typedef struct node Node;

struct node
{
    int data;
    Node* next;
};

//declare your function here.
void print(Node *list);
Node* reverse(Node * list){
    Node* before = NULL;
    Node* i = list;
    Node* next;
    
    
    while(i != NULL){
        next = i->next;
        i->next = before;
        before = i;
        i = next;
    }
    return before;
}


int main(int argc, char* argv[])
{
    Node* head = NULL;
    int i;
    Node* temp;
    
    //set up a test list with values 9->8->7->...->0
    for (i = 0; i < 10; i++)
    {
        temp = (Node*)malloc(sizeof(Node));
        if (temp == NULL)
        {
            printf("out of memory?\n");
            exit(1);
        }
        temp->data = i;
        temp->next = head;
        head = temp;
    }
    
    //call your function to reverse the list (should work for any list given the head node).
    
    temp = head;
    print(temp);

    temp = reverse(head);
    print(temp);
    
    return 0;
}

void print(Node *list)
{
    Node *temp = list;
    while (temp != NULL)
    {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}
