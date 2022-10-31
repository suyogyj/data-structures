#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *nextPtr;
};
typedef struct node listNode;
typedef listNode *nodePtr;

void insert(nodePtr *ptr, int num){

    nodePtr newPtr;
    nodePtr prevPtr;
    nodePtr curPtr;

    newPtr = malloc(sizeof(listNode));

    if(newPtr != NULL){
        newPtr->value = num;
        newPtr->nextPtr = NULL;

        prevPtr = NULL;
        curPtr = *ptr;

        while(curPtr != NULL && num > curPtr->value){
            prevPtr = curPtr;
            curPtr = curPtr->nextPtr;
        }
        if(prevPtr == NULL){
            newPtr->nextPtr = *ptr;
            *ptr = newPtr;
        }
        else {
            prevPtr->nextPtr = newPtr;
            newPtr->nextPtr = curPtr;
        }
    }

    else{
        printf("no");
    }
}

void reverse(nodePtr** head){

    nodePtr prevPtr = NULL;
    nodePtr curPtr = *head;
    nodePtr nextPtr = NULL;

    while(curPtr != NULL){
        nextPtr = curPtr->nextPtr;
        curPtr->nextPtr = prevPtr;
        prevPtr = curPtr;
        curPtr = nextPtr;
    }

    *head = prevPtr;

}

void printLinkedList(nodePtr p){

    while(p != NULL){
        printf("%d ,", p->value);
        p  = p->nextPtr;
    }
}

int main() {
    nodePtr startPtr = NULL;
    int item;
    int length;
    printf("Input length of list: ");
    scanf("%d", &length);
    int i;
    for(i = 0; i < length; i++){
        printf("Enter a number: ");
        scanf("%d", &item);
        insert(&startPtr, item);
    }
    printLinkedList(startPtr);
    printf("\n");
    reverse(&startPtr);
    printLinkedList(startPtr);

}
