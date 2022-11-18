#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node
{
    int val;
    struct node* left;
    struct node* right;
    int height;
};

typedef struct node treeNode;
typedef treeNode* NodeAddress;

int maxN(int x, int y)
{
    if(x >= y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

int* randArr(int n)
{
    int* arr = malloc(n*sizeof(int));
    srand(time(NULL));
    for(int i = 0; i < n; i++)
    {
        arr[i] = rand()%1000;
    }
    return arr;
}

NodeAddress minNode(NodeAddress head)
{
    NodeAddress curr = head;
    if(!(curr->left))
    {
        return curr;
    }

    else
    {
        return minNode(curr->left);
    }
}

treeNode* makeNode(int n)
{
    NodeAddress newNode = (NodeAddress)malloc(sizeof(treeNode));
    newNode->val = n;
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->height = 1;
    return newNode;

}

int treeHeight(NodeAddress head)
{
    if(!head)
    {
        return 0;
    }
    
    return head->height;
    
}

int treeHeightDifference(NodeAddress head)
{
    if(!head)
    {
        return 0;
    }
    
    return (treeHeight(head->left) - treeHeight(head->right));
    
}

NodeAddress leftRotate(NodeAddress head)
{
    NodeAddress rightC = head->right;
    NodeAddress leftS = rightC->left;

    rightC->left = head;
    head->right = leftS;
    head->height = maxN(treeHeight(head->left), treeHeight(head->right)) + 1;
    rightC->height = maxN(treeHeight(rightC->left), treeHeight(rightC->right)) + 1;

    return rightC;
}

NodeAddress rightRotate(NodeAddress head)
{
    NodeAddress leftC = head->left;
    NodeAddress rightS = leftC->right;

    leftC->right = head;
    head->left = rightS;
    head->height = maxN(treeHeight(head->left), treeHeight(head->right)) + 1;
    leftC->height = maxN(treeHeight(leftC->left), treeHeight(leftC->right)) + 1;

    return leftC;
}

NodeAddress balance(NodeAddress head)
{
    int bal = treeHeightDifference(head);

    if(treeHeightDifference(head->left) >= 0&& bal > 1)
    {
        return rightRotate(head);
    }

    if(treeHeightDifference(head->right) <= 0 && bal < -1 )
    {
        return leftRotate(head);
    }

    if(treeHeightDifference(head->left) < 0 && bal > 1)
    {
        head->left = leftRotate(head->left);
        return rightRotate(head);
    }

    if(treeHeightDifference(head->right) > 0 && bal < -1)
    {
        head->right = rightRotate(head->right);
        return leftRotate(head);
    }
    return head;
}

NodeAddress insert(NodeAddress head, int n)
{
    if(head == NULL)
    {
        return makeNode(n);
    }
    else if(n < head->val)
    {
        head->left = insert(head->left, n);
    }
    else if(n > head->val)
    {
        head->right = insert(head->right, n);
    }
    else{
        return head;
    }
    
    head->height = maxN(treeHeight(head->left), treeHeight(head->right)) + 1;
    return balance(head);
}

NodeAddress delete(NodeAddress head, int n)
{
    if(!head)
    {
        return head;
    }
    else if (n > head->val)
    {
        head->right = delete(head->right, n);
    }
    else if (n < head->val)
    {
        head->left = delete(head->left, n);
    }
    else
    {
        NodeAddress t = NULL;
        if(!(head->left) && !(head->right))
        {
            free(head);
            return t;
        }
        else if(!(head->left))
        {
            t = head->right;
            free(head);
            return t;
        }
        else if(!(head->right))
        {
            t = head->left;
            free(head);
            return t;
        }
        else
        {
            NodeAddress s = minNode(head);
            head->val = s->val;
            free(s);        
            }
    }
}   
    
void printInOrder(NodeAddress head) //left->root->right
{
    if(head->left)
    {
        printInOrder(head->left);
    }

    if(head)
    {
        printf("%d, ", head->val);
    }

    if(head->right)
    {
        printInOrder(head->right);
    }
}

NodeAddress makeTree(int* a, int n)
{
    NodeAddress head = NULL;
    if(n > 0)
    {
        head = makeNode(a[0]);
        for(int i = 1; i < n; i++)
        {
            head = insert(head, a[i]);
        }
    }
    return head;
}


int main()
{
    int* arr = randArr(5); //makes an array of length 5 with randomised values.
    
    NodeAddress head = makeTree(arr, 5);
    printInOrder(head);

    insert(head, 22);
    insert(head, 715);
    insert(head, 0);
    printf("\n");
    printInOrder(head);

    delete(head, 22);
    delete(head, 0);

    printf("\n");
    printInOrder(head);
}