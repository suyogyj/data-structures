#include <stdio.h>
#include <stdlib.h>

struct node
{
	int val;
	struct node* right;
	struct node* left;
};

typedef struct node* NodeAddress;
typedef struct node listNode;

int minimum(int x, int y)
{
	int minimum = 0;

	if(x==y)
    {
		minimum = x;
	}

	else if(x < y)
    {
		minimum = x;
	}

	else
    {
		minimum = y;
	}

	return minimum;
}


int dist(NodeAddress head, int l, int g){       //geeksforgeeks
	int sum = 0;
	
	if(head == NULL){
		return 0;
	}

	if(l == head->val && g == head->val){
		return 1;
	}
	if(l< head->val <g){
		sum = 1 + dist(head->left, l, g)+dist(head->right, l, g);
	}

	if(l >= head->val){
		return dist(head->left, l, g);
	}

	else if(g <= head->val){
		return dist(head->right, l, g);
	}
	return sum;
}

int nodeSearch(NodeAddress head, int k){    //geeksforgeeks

	if(head == NULL){
		return 0;
	}

	if(head->val == k){
		return 1;
	}

	else if(head->val>k){
		return nodeSearch(head->right, k);
	}

	else{
		return nodeSearch(head->left,k);
	}

}


int sortedDistance(NodeAddress head, int x, int y){
	int distance = 0;
	int l, g;

	l = minimum(x,y);

	if(l == x){
		g = y;
	}
	else{
		g = x;
	}

	int lreal = nodeSearch(head, l);
	int greal = nodeSearch(head, g);

	if(lreal == 1 && greal ==1){
		distance = dist(head, l, g);
	}
	else{
		distance = -1;
	}

	return distance;
}

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
    
    int x = 82;
    int y = 2;

    NodeAddress head = arrayToReverseBST(arr, n);

	prefixPrint(head);
    printf("\n");
	printf("There are %d numbers b/w x and y", sortedDistance(head, x,y));
}

