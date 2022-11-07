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

//swap elements
void swap(listNode** nHead, listNode* head, listNode* min, listNode* cMin){

    *nHead = min;

    cMin->nextPtr = head;

    listNode* t = min->nextPtr;
    min->nextPtr = head->nextPtr;
    head->nextPtr = t;

}

listNode* findLastNode(listNode* head)
{
    listNode* temp = head;
    while(temp != NULL && temp->nextPtr != NULL)
    {
        temp = temp->nextPtr;
    }
    return temp;
}

listNode* partition(listNode* head, listNode* lastNode)
{
    listNode* pivot = head;
    listNode* startNode = head;

    int t = 0;

    while(startNode != NULL && startNode != lastNode)
    {
        if(startNode->value < lastNode->value)
        {
            pivot = head;
            
            //swap head and startNode
            t = head->value;
            head->value = startNode->value;
            startNode->value = t;

           head = head->nextPtr;
        }
        startNode = startNode->nextPtr;
    }

    t = head->value;
    head->value = lastNode->value;
    lastNode->value = t;
    return pivot;
    

}

listNode* quickSort(listNode* head, listNode* lastNode)
{
    if(head == lastNode)
    {
        return;
    }

    listNode* pivot = partition(head, lastNode);

    if(pivot != NULL && pivot->nextPtr != NULL)
    {
        quickSort(pivot->nextPtr, lastNode);
    }

    if(pivot != NULL && head != pivot)
    {
        quickSort(head, pivot);
    }
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
    listNode *s = quickSort(head, findLastNode(head));

    printLinkedList(s);


}

