#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node* nextPtr;
};

typedef struct node listNode;
typedef listNode* nodePtr;

nodePtr head = NULL;
nodePtr sorted = NULL;

//insert a new node in the linked list

void insert(listNode** head, int num){

    listNode* newPtr = malloc(sizeof(struct node));

    newPtr->value = num;
    newPtr->nextPtr = (*head);
    (*head) = newPtr;

}

//swap elements (for selectionSort)
void swap(listNode** nHead, listNode* head, listNode* min, listNode* cMin){

    *nHead = min;

    cMin->nextPtr = head;

    listNode* t = min->nextPtr;
    min->nextPtr = head->nextPtr;
    head->nextPtr = t;

}


void insertInSorted(listNode* x)
{

    if(sorted == NULL || sorted->value >= x->value)
    {

        x->nextPtr = sorted;
        sorted = x;
    }

    else
    {
        listNode* curr = sorted;

        while(curr->nextPtr != NULL && curr->nextPtr->value < x->value)
        {
            curr = curr->nextPtr;
        }

        x->nextPtr = curr->nextPtr;
        curr->nextPtr = x;
    }

}


listNode* insertionSortLL(listNode* head)
{

    listNode* curr = head;

    while(curr != NULL)
    {

        listNode* next = curr->nextPtr;

        insertInSorted(curr);

        curr = next;

    }

    head = sorted;

}

void printLinkedList(nodePtr p){

    while(p != NULL){
        printf("%d ,", p->value);
        p = p->nextPtr;
    }
}

int main() {

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
    printf("List: \n");
    printLinkedList(head);
    printf("\n");
    listNode *s = insertionSortLL(head);

    printLinkedList(s);


}

