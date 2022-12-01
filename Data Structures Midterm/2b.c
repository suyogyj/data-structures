#include <stdio.h>
#include <stdlib.h>

//printLinkedList, reverse, and basic code to create linked list is from my github

struct node
{
    int val;
    struct node *next;
    struct node *next2;
};

typedef struct node listNode;
typedef listNode *NodeAddress;

//based on reverse function from my github submission
//reverses list and sets all next2 = NULL, then iterates over the list again to set correct next2 values.
NodeAddress reverseLLWithNext2(NodeAddress head){
    NodeAddress prevPtr = NULL;
    NodeAddress curPtr = head;
    NodeAddress nextPtr = NULL;

    while(curPtr != NULL){
        curPtr->next2 = NULL;
        nextPtr = curPtr->next;
        curPtr->next = prevPtr;
        prevPtr = curPtr;
        curPtr = nextPtr;
    }
    head = prevPtr;
    NodeAddress n2 = prevPtr;
    while(n2->next->next != NULL)
    {
        n2->next2 = n2->next->next;
        n2 = n2->next;
    }
    return head;
}

NodeAddress arrayToLLWithNext2(int *a, int n)
{
    NodeAddress head = NULL;
    NodeAddress temp = NULL;

    int i = 0;

    for (i = 0; i < n; i++)
    {
        NodeAddress newNode = (NodeAddress)malloc(sizeof(listNode));

        newNode->val = a[i];
        newNode->next = NULL;
        newNode->next2 = NULL;
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

    NodeAddress n2 = head;
    for(i = 0; i < n; i++)
    {
        if(n2->next->next != NULL)
        {
            n2->next2 = n2->next->next;
        }

        else
        {
            break;
        }
        n2 = n2->next;
    }
    return head;
}

//print function from my github submission
void printLinkedList(NodeAddress head){

    NodeAddress t = head;
    while(head != NULL){
        printf("%d ,", head->val);
        head = head->next;
    }
    printf("\n");
    while(t != NULL){
        printf("%d ,", t->val);
        t = t->next2;
    }
    printf("\n");
}

int main()
{
    int arr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12, 13, 14, 15, 16, 17, 18};
    int size = sizeof(arr) / sizeof(arr[0]);
    NodeAddress head = arrayToLLWithNext2(arr, size);
    NodeAddress t = reverseLLWithNext2(head);
    printLinkedList(t);
}

