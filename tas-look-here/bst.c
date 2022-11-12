#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node
{
    int value;
    struct node *left, *right;
};
typedef struct node listNode;


listNode* makeNewNode(int num)
{
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->value = num;
    node->left = node->right = NULL;
}


listNode* insert(int arr[], int a, int b)
{
    listNode* root = NULL;

    if(a<b)
    {
        root = makeNewNode(arr[a]);

        root->left = insert(arr, 2*a+1, b);

        root->right = insert(arr, 2*a+2,b);
    }

    return root;
}

void printBST(listNode* root)
{
    if(root != NULL)
    {
        printBST(root->left);
        printf("%d ", root->value);
        printBST(root->right);
    }
}

int main()
{
    int arr[] = {4, 4, 2, 3, 10, 39, 6};
    int size = sizeof(arr)/sizeof(arr[0]);

    listNode* head = insert(arr, 0, size);
    printBST(head);
}