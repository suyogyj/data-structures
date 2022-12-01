#include <stdio.h>
#include <stdlib.h>

//printLinkedList and basic code to create linked list is from my github

struct node
{
    int val;
    struct node *next;
    struct node *next2;
};

typedef struct node listNode;
typedef listNode *NodeAddress;

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
        head = head->next2;
    }
    printf("\n");
    while(t != NULL){
        printf("%d ,", t->val);
        t = t->next;
    }
}


int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 38, 28192, 282};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", size);
    NodeAddress head = arrayToLLWithNext2(arr, size);
    printLinkedList(head);
}