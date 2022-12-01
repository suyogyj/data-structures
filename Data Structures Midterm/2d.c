#include <stdio.h>
#include <stdlib.h>

//printLinkedList and basic code to create linked list is from my github

struct node
{
    int val;
    struct node *next;
    struct node *nextk;
    int k;

};

typedef struct node listNode;
typedef listNode *NodeAddress;


NodeAddress arrayToLLWithNextK(int *a, int n)
{
    NodeAddress head = NULL;
    NodeAddress temp = NULL;

    int i = 0;
    
    for (i = 0; i < n; i++)
    {
        NodeAddress newNode = (NodeAddress)malloc(sizeof(listNode));
        int k = rand()%(5-2 + 1) + 2;   //sets k to a random number between 2 and 5
        newNode->val = a[i];
        newNode->next = NULL;
        newNode->k = k;
        newNode->nextk = NULL;
        if (head == NULL)
        {
            head = newNode;
        }

        else
        {
            temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newNode;
            
        }
    }
    NodeAddress nk = head;
    for(i = 0; i < n; i++)
    {
        int k = nk->k;
        NodeAddress nc = nk;
        for(int j = 0; j < k; j++)
        {
            if(nc->next != NULL)
            {
                nc = nc->next;
            }
            else
            {
                nc = NULL;
                break;
            }
        }
        nk->nextk = nc;
        nk = nk->next;
    }
    return head;
}

NodeAddress reverseLLWithNextK(NodeAddress head)
{
    NodeAddress prevPtr = NULL;
    NodeAddress curPtr = head;
    NodeAddress nextPtr = NULL;

    while(curPtr != NULL){
        curPtr->nextk = NULL;
        nextPtr = curPtr->next;
        curPtr->next = prevPtr;
        prevPtr = curPtr;
        curPtr = nextPtr;
    }

    head = prevPtr;

    NodeAddress nk = prevPtr;
    while(nk->next != NULL)
    {
        NodeAddress nc = nk;
        int k = nk->k;
        for(int i = 0; i < k; i++)
        {
            if(nc->next != NULL)
            {
                nc = nc->next;
            }

            else
            {
                nc = NULL;
                break;
            }
        }
        nk->nextk = nc;
        nk = nk->next;
    }
    return head;

}

void printLinkedList(NodeAddress head){

    NodeAddress t = head;
    while(head != NULL){
        printf("%d, ", head->val);
        head = head->next;
    }
    printf("\n");
    while(t != NULL){
        printf("%d ,", t->val);
        t = t->nextk;
    }
    printf("\n");
}

int main()
{
    int arr[] = {24, 12, 26, 13, 72, 69, 2, 14, 52, 19, 38, 2, 23};
    int size = sizeof(arr) / sizeof(arr[0]);
    NodeAddress head = arrayToLLWithNextK(arr, size);
    NodeAddress t = reverseLLWithNextK(head);
    printLinkedList(t);
}