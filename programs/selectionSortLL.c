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
    reverse(&head);
    printf("Reversed list: \n");
    printLinkedList(head);

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
