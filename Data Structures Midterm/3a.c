#include <stdio.h>
#include <stdlib.h>

//This program is basically the same as a regular BST creation program, just the left node is bigger than the right instead of the other way around.

struct node
{
	int val;
	struct node* right;
	struct node* left;
};

typedef struct node* NodeAddress;
typedef struct node listNode;



void prefixPrint(NodeAddress head) //print in prefix order
{
	if (head == NULL)
        return;
	
	printf("%d ", head->val);
 
	prefixPrint(head->left);
 
	prefixPrint(head->right);
}

NodeAddress make(int i) //create new node
{
	NodeAddress head = (NodeAddress)malloc(sizeof(listNode));

	head->val = i;
	head->left = head->right = NULL;

	return head;
}

NodeAddress insert(NodeAddress head, int i)  //insert node in BST. from my github.
{
	if(head == NULL)
    {
		return make(i);
	}

	else if(i < head->val)
    {
		head->right = insert(head->right, i);
	}

	else
    {
		head->left = insert(head->left, i);
	}

	return head;
}

NodeAddress arrayToReverseBST(int *a, int n)
{
    NodeAddress head = make(a[0]);

	for(int count = 1; count<n; count++)
    {
		insert(head, a[count]);
	}
    return head;
}

int main()
{
	int arr[] = {82, 8123, 31, 2, 10, 81, 53};
	int n = sizeof(arr)/sizeof(arr[0]);
    NodeAddress head = arrayToReverseBST(arr, n);
	prefixPrint(head);
}