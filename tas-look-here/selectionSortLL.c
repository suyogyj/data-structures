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

//swap elements (for selectionSort)
void swap(listNode** nHead, listNode* head, listNode* min, listNode* cMin){

    *nHead = min;

    cMin->nextPtr = head;

    listNode* t = min->nextPtr;
    min->nextPtr = head->nextPtr;
    head->nextPtr = t;

}

listNode* selectionSort(listNode* head){

    if(head->nextPtr == NULL)
    {
        return head;
    }
    listNode* min = head, * cMin = NULL, * t;

    for(t = head; t->nextPtr != NULL; t = t->nextPtr)
    {
        if(t->nextPtr->value < min->value)
        {
            min = t->nextPtr;
            cMin = t;
        }
    }

    if(min != head)
    {
        swap(&head, head, min, cMin);
    }

    head->nextPtr = selectionSort(head->nextPtr);

    return head;

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
    printf("List: \n");
    printLinkedList(head);
    printf("\n");
    listNode *s = selectionSort(head);

    printLinkedList(s);


}

//
//findAddressOfMax(int* a, int n)
//{
//
//    int* amax;
//    int i;
//    amax = a;
//
//    for(i = 1; i < n; i+=1)
//    {
//        a = a+i;
//        if(*a > *amax){
//            amax = a;
//        }
//    }
//
//    return amax;
//
//}
