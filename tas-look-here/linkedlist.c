#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node* nextPtr;
};
typedef struct node listNode;
typedef listNode* nodePtr;

//insert a new node in the linked list

void insert(listNode** head, int num){

    listNode* newPtr = malloc(sizeof(struct node));

    newPtr->value = num;
    newPtr->nextPtr = NULL;

    if(*head == NULL)
    {
        *head = newPtr;
        return;
    }

    listNode *temp = *head;
    
    while(temp->nextPtr != NULL)
    {
        temp = temp->nextPtr;
    }

    temp->nextPtr = newPtr;

}


void printLinkedList(nodePtr p){

    while(p != NULL){
        printf("%d ,", p->value);
        p = p->nextPtr;
    }
}

int main() {
    nodePtr head = NULL;
    int item;
    int length;
    printf("Input length of list: ");
    scanf("%d", &length);
    int i;
    for(i = 0; i < length; i++){
        printf("Enter a number: ");
        scanf("%d", &item);
        insert(&head, item);
    }
    printLinkedList(head);
    printf("\n");
    reverse(&head);
    printLinkedList(head);

}
