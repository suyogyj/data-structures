#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


//struct for a single node in the fib heap
struct fibHeapNode
{
    int value;
    int degree; 
    struct fibHeapNode *left;
    struct fibHeapNode *right;
    struct fibHeapNode *parent;
    struct fibHeapNode *child;
    char mark;
};

typedef struct fibHeapNode* NodeAddress;


//struct for the fib heap
struct fibHeap
{
    int size;
    NodeAddress min;
};

typedef struct fibHeap fibHeap;

//make a new fib heap node
NodeAddress newNode(int value)
{
    NodeAddress temp = (NodeAddress)malloc(sizeof(struct fibHeapNode));
    temp->value = value;
    temp->degree = 0;
    temp->parent = NULL;
    temp->child = NULL;
    temp->left = temp;
    temp->right = temp;
    temp->mark = 0;

    return temp;
}

//make a new fib heap
fibHeap *newHeap()
{
    fibHeap *heap = (fibHeap *)malloc(sizeof(struct fibHeap));
    heap->size = 0;
    heap->min = NULL;

    return heap;
}

//function to merge two fib heaps
NodeAddress mergeHeaps(fibHeap *heap, NodeAddress x, NodeAddress y)
{
    //if one heap is empty, then there is nothing to merge. return the other heap.
    if(x == NULL){
        return y;
    }
    if(y == NULL){
        return x;
    }

    //merge the heaps. add the heap with the smaller root to the other heap
    if(x->value > y->value)
    {
        NodeAddress temp = x;
        x = y;
        y = temp;
    }

    //make y a child of x
    NodeAddress right = x->right;
    y->right = right;
    y->left = x;
    x->right = y;
    right->left = y;

    //increase degree of x
    x->degree += 1;

    return x;
}

//decrease the key(value) of a node
void decreaseKey(fibHeap *heap, NodeAddress node, int value)
{
    node->value = value;

    //if the node is a root, check if it needs to moved to the front of the root list
    if(node->parent == NULL)
    {
        if(node->value < heap->min->value){
            heap->min = node;
        }
        return;
    }

    //if the parent has a higher value, cut the node from the tree, and move it to the root list
    if(node->parent->value > node->value)
    {
        if(node->right == node){
            node->parent->child = NULL;
        }
        else
        {
            node->right->left = node->left;
            node->left->right = node->right;
            if(node->parent->child == node){
                node->parent->child = node->right;
            }
        }

        //add the node to the root list
        node->right = heap->min;
        node->left = heap->min->left;
        heap->min->left = node;
        node->left->right = node;
        node->parent = NULL;
        node->child = NULL;
        node->degree = 0;


        //if th eparent has no children, set the mark to 0
        if(node->parent != NULL && node->parent->child == NULL)
        {
            node->parent->mark = 0;
        }

        //if the parent of the node has a greater value, again cut the node from the tree and move it to the root list.
        if(node->parent->value > node->value)
        {
            decreaseKey(heap, node->parent, node->value);
        }
    }
}

NodeAddress extractMin(fibHeap *heap)
{
    NodeAddress min = heap->min;
    
    //if the heap only has one node, set the min pointer to NULL.
    if(min->right == min){
        heap->min = NULL;
    }
    else
    {
        min->right->left = min->left;
        min->left->right = min->right;
        heap->min = min->right;

        // Merge the children of the minimum node with the root list of the heap
        NodeAddress child = min->child;
        if (child != NULL)
        {
            do
            {
                child->parent = NULL;
                child = child->right;
            } while (child != min->child);

            heap->min = mergeHeaps(heap, heap->min, min->child);
        }
    }

    // Decrease the size of the heap
    heap->size--;

    // Return the minimum node
    return min;
}

//func to return the minimum node in the heap
NodeAddress findMin(fibHeap *heap)
{
    return heap->min;
}

//func to insert a node into the heap
void insert(fibHeap *heap, NodeAddress node)
{
    heap->min = mergeHeaps(heap, heap->min, node);
    heap->size = heap->size++;
}
//func to delete a node from the heap
void delete(fibHeap *heap, NodeAddress node)
{
    decreaseKey(heap, node, INT_MIN);
    extractMin(heap);
}
//func to print the heap
void printHeap()
{

}

//function to generate random numbers to insert into the heap (for testing)

int main(int argc, char *argv[])
{

    fibHeap *heap = newHeap();

    insert(heap, newNode(31));
    insert(heap, newNode(12));
    insert(heap, newNode(21));
    insert(heap, newNode(122));

    NodeAddress min = findMin(heap);

    printf("%d ", min->value);

    

}