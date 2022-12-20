#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

//struct for a single node in the fib heap
struct fibHeapNode
{
    int value;  //value stored
    int degree; //nodes attached
    struct fibHeapNode *left;
    struct fibHeapNode *right;
    struct fibHeapNode *parent;
    struct fibHeapNode *child;
    int find;   //used for findNode function
    char mark;  //used for cascade cut function
};      

typedef struct fibHeapNode* NodeAddress;


//struct for the fib heap
struct fibHeap
{
    int size;   //size of the heap
    NodeAddress min;//minimum node in the heap
};

typedef struct fibHeap fibHeap;

//make a new fib heap node
NodeAddress newNode()
{
    NodeAddress temp = (NodeAddress)malloc(sizeof(struct fibHeapNode));
    temp->degree = 0;
    temp->parent = NULL;
    temp->child = NULL;
    temp->mark = 0;
    temp->find = 0;

    return temp;
}

//make a new empty heap
fibHeap *newHeap()
{
    fibHeap *heap = (fibHeap *)malloc(sizeof(struct fibHeap));
    heap->size = 0;
    heap->min = NULL;

    return heap;
}


//insert a node in the heap
void insertHelper(fibHeap *heap, NodeAddress node)
{
    if(heap->min == NULL){  //if there is no min, make the new node the min
        heap->min = node;
    }

    else
    {
        if(heap->min->right == heap->min)   //if there is only one node in the root list, add the new node to the root list
        {
            heap->min->left = node;
            heap->min->right = node;
            node->left = heap->min;
            node->right = heap->min;
        }
        else
        {                                   //Otherwise, add the new node to the right of the min node
            node->right = heap->min->right;
            node->left = heap->min;
            heap->min->right->left = node;  //make the min node's old right node be the new node's right node
            heap->min->right = node;
        }
        if(node->value < heap->min->value){ //if new node is smaller than min, make it the min
            heap->min = node;
        }
    }
}

void insert(fibHeap *heap, int value)
{
    NodeAddress node = newNode();           //make a new node
    node->value = value;
    node->left = node;
    node->right = node;
    insertHelper(heap,node);                //insert it into the heap
    heap->size = heap->size+1;              //increase the size of the heap
}

//merge two heaps
fibHeap *mergeHeaps(fibHeap* heap1, fibHeap* heap2)
{
    fibHeap *temp = newHeap();              //create new heap
    temp->min = heap1->min;                 //new heap's min = heap1 min
    temp->size = heap1->size + heap2->size; //new heap's size = combined size of the two heaps to be merged
    if (heap1->min != NULL && heap2->min != NULL) //
    {
        NodeAddress temp1 = heap1->min->right;      
        NodeAddress temp2 = heap2->min->left;

        heap1->min->right = heap2->min;         //concatenate the root lists of the two heaps
        heap2->min->left = heap1->min;
        temp1->left = temp2;
        temp2->right = temp1;
    }
    
    if(heap1->min == NULL || (heap2->min != NULL && (heap2->min->value < heap1->min->value))){
        temp->min = heap2->min;
    }

    return temp;
}

//cut a node from the heap. this involves moving a node from being a child of another node to being a root node in the heap
void cut(fibHeap *heap, NodeAddress c, NodeAddress p)
{
    if(p->child == c)           //check if c is the child of p
    {
        if(c->right == c){      //if it is the only child, remove it from being the child of p
            p->child = NULL;
        }
        else{                   //else, set p's child as the right child of c
            p->child = c->right;
        }
    }
    if(p->child != NULL)        //update pointers to remove c from the children of p
    {
        c->right->left = c->left;
        c->left->right = c->right;
    }

    insertHelper(heap, c);      //add c to the root list of the heap
    c->parent = NULL;           //set c's parent value to null to indicate it is no longer a child
    c->mark = 0;
    p->degree--;                //decrement degree of p, because c is no longer a child.

}


//cascading cut, to decrease time for decrease key func
//responsible for maintaining the heap's structure after a node has been removed.
//recursively cuts
void cascadingCut(fibHeap *heap, NodeAddress node)
{
    NodeAddress p = node->parent;
    if(p != NULL)                   //if the node has a parent
    {
        if(node->mark == 0)         //if the node isn't marked, mark it
        {
            node->mark = 1;
        }
        else
        {
            cut(heap, node, p);     //cut the node from it's parent
            cascadingCut(heap, p);  //call cascadingcut on the parent
        } 
    }
}

//decrease the value of a given node (used in algorithms such as Dijkstra's)
void decreaseKey(fibHeap *heap, NodeAddress node, int value)
{
    if(heap->min == NULL)
    {
        printf("\n Error, heap is empty.");
    }

    else if (node->value < value)
    {
        printf("\n Error, the new value is greater than the old value");
    }

    else
    {
        node->value = value;                                //update value of the node
        NodeAddress temp = node->parent;    
        if(temp != NULL && (node->value < temp->value))     //check if the node needs to be cut and moved to the top of the heap
        {
            cut(heap, node, temp);                          //if yes, cut it and other necessary cuts
            cascadingCut(heap, temp);
        }

        if(node->value < heap->min->value)                  //if the node's value is lower than the current minimum, set it as the minimum
        {
            heap->min = node;
        }
    }  
}

//link two subtrees in the heap by making one a child of the other.
void link(fibHeap* heap, NodeAddress x, NodeAddress y)
{
    (x->left)->right = x->right;        //remove x from its list of siblings
    (x->right)->left = x->left;

    if(y->right == y)                   //if y is the only node in its list of siblings, make it the minimum node of the heap
    {
        heap->min = y;                  
    }

    x->left=x;                          //set left and right pointers of x to point to itself, and its parent to y
    x->right=x;
    x->parent=y;

    if(y->child==NULL)                  //if y has no other childrem, make x its child
    {
        y->child=x;
    }
    else                                //if y has children, insert x into the list of y's children
    {
        x->right=y->child;
        x->left=(y->child)->left;
        ((y->child)->left)->right=x;
        (y->child)->left=x;
    }

    if(x->value<(y->child)->value)      //if the value of x is less than the value of the current min, update the min child of y to be x
    {
        y->child = x;
    }

    y->degree+=1;                      
    x->mark=0;
}

int degree(fibHeap *heap)
{
    return (log2(heap->size)) + 1;      //
}

void consolidate(fibHeap* heap){
    int deg = degree(heap);
    NodeAddress *x;                             //create an array of NodeAddresses with degree+1 elements
    x = (NodeAddress*)malloc((deg+1)*sizeof(NodeAddress)); 

    for(int i=0; i<=deg; i++){                             
        x[i]=NULL;
    }

    NodeAddress temp2 = heap->min;              //temp1 = temp2 = min                  
    NodeAddress temp1 = temp2;

    do{
        int d=temp2->degree;

        while(x[d] != NULL){
            NodeAddress temp3 = x[d];

            if(temp2->value > temp3->value)     //if temp2 > temp3, swap them
            {
                NodeAddress temp4=temp3;
                temp3=temp2;
                temp2=temp4;    
            }

            link(heap,temp3,temp2);             //link temp3 and temp2

            if(temp1 == temp3){                 //if temp1 is pointing to temp3, make it point to temp2
                temp1 = temp2;
            }

            x[d] = NULL;
            d++;
        }

        x[d] = temp2;                                       
        temp2 = temp2->right;
    }while(temp2 != temp1);

    heap->min = NULL;

    for(int i=0; i<=deg; i++){                              
        if(x[i] != NULL){
            if(heap->min == NULL){              //if minimum is empty, make x[i] the new min
                heap->min = x[i];
                x[i]->left = x[i];
                x[i]->right = x[i];
            }

            else{
                insertHelper(heap, x[i]);       //otherwise, add x[i] to the root list.
                if(x[i]->value < heap->min->value)
                    heap->min = x[i];
            }
        }
    }
}

int extractMin(fibHeap* heap)
{
    if(heap->min!=NULL)
    {
        NodeAddress temp = heap->min;           //Save the minimum pointer
        NodeAddress find = temp;
        NodeAddress x = NULL;

        if(temp->child != NULL)                 //Check if the heap is mempty or not
        {
            x=temp->child;                      //if not empty, then add all the children to the root list

            do
            {
                find = x->right;                // Set find to the right child of x

                heap->min->left->right = x;     // Update the ponters between the nodes to move x to the root list of the heap
                x->right=heap->min;
                x->left=heap->min->left;
                heap->min->left=x;

                if(x->value < heap->min->value) // If the value of x is less than the value of the current minimum node, update the min field
                {
                    heap->min = x;
                }

                x->parent = NULL;               // Set the parent of x to NULL to indicate that it is now a root node in the heap
                x = find;                       // Set x to find and continue the loop until find is equal to the child of temp
            }while(find != temp->child);
        }

        temp->left->right = temp->right;        //remove temp from the heap
        temp->right->left = temp->left;
        heap->min=temp->right;                  //set the min to temp's right

        if(temp == temp->right && temp->child == NULL){ 
            heap->min = NULL;
        }
        else 
        {
            heap->min = temp->right;
            consolidate(heap);
        }

        heap->size--;

        return temp->value;
    }
}

void findNode(fibHeap *heap,NodeAddress node, int value,int newValue,int *done)
{
    NodeAddress temp = node;
    temp->find = 1;

    if(temp->value == value)                //if temp holds the value that we're looking for, done
    {
        *done = 1;
        temp->find = 0;
        decreaseKey(heap,temp,newValue);    //set the value of the found node to what we want
        return;
    }
    else                                    //otherwise, recursively call findNode
    {
        if(temp->child != NULL){            //if temp has a child, call findNode on the child
            findNode(heap, temp->child ,value, newValue, done);
        }
        if(!temp->right->find){             //ifthe find field of temp's right is 0, call findNode on temp->right
            findNode(heap, temp->right, value, newValue, done);
        }
    }
    temp->find = 0;
}

//func to delete a node from the heap
void delete(fibHeap *heap, int value, int *done)
{
    findNode(heap, heap->min, value, INT_MIN, done);    //make the value of the node we want to the minimum possible
    int temp = extractMin(heap);                        //extract the minimum node in the heap
}

//func to print the heap
void printHeap(NodeAddress node, char *s, int x)
{
    NodeAddress temp = node;
    s[x] = '\\';
    s[++x] = '\0';
    do
    {
        printf("%s, %d\n", s, temp->value);
        if(temp->child != NULL)
        {
            printHeap(temp->child, s, x);
        }
        temp = temp->right;
    } while (temp != node);
    
}

int inputMachine(char *s)
{
    char num[2];

    while(true)                         //scans all input as a string,
    {
        printf("%s",s);
        scanf("%s", &num);
        int inputToInt = atoi(num);     //converts it to an int
        inputToInt = (inputToInt - 1) + 1;  //sometimes, string ASCII input gets interpreted as 00, which isn't the same as 0. incrementing and decrementing resets it to 0

        return inputToInt;
    }
}

int *generate_random_array(int n) {       //generates 'n' random integers and stores them in an array
  int * t = malloc(n * sizeof(int));
	if (t){
		for(int i=0;i<n;i++){
			t[i]=rand()%30;
		}
	}
	return t;
}

void tester(fibHeap** heap)
{   
    int *done = (int*)malloc(sizeof(int));
    done = 0;
    int *arr = generate_random_array(50);   //make a random array with 50 ints
    for(int i = 15; i < 20; i++)
    {
        insert(heap[1], arr[i]);            //insert 5 values from the array in heap 1
    }
    for(int i = 25; i < 30; i++)
    {
        insert(heap[2], arr[i]);            //insert 5 values from the array in heap 2
    }
    char s[100] = "";
    printHeap(heap[1]->min, s, 0);          //print heap 1
    printf("\n");
    mergeHeaps(heap[1], heap[2]);           //merge heap 1 and heap 2
    char p[100] = "";
    printf("\n");
    printHeap(heap[1]->min, p, 0);          //print the new, merged heap

    int value = extractMin(heap[1]);        //extract the minimum value from the new heap
    printf("\n The minimum value extracted is %d", value);  
    value = extractMin(heap[1]);            //extract again
    printf("\n The minimum value extracted is %d", value);


}


int main(int argc, char *argv[])
{
    fibHeap** heap;         //a list of heaps
    bool test = false;      //if test = true, tester function is called and interface is skipped
    int choice = 0;         
    int job = 0;
    int num = -1;
    char *s = "Enter the number of heaps you want to make: ";
    num = inputMachine(s);
    while(true)
    {
        if(num == 0)
        {
            printf("%d", num);
            printf("Input is invalid, please enter a positive integer value.\n");
            num = inputMachine(s);
        }
        else if(num < 0)
        {
            printf("%d", num);
            printf("Input is invalid, please enter a positive integer value.\n");
            num = inputMachine(s);
            
        }
        else
        {
            printf("%d", num);
            break;
        }
    }
    heap = (fibHeap**)malloc(num*sizeof(fibHeap*));        

    for(int i = 1; i <= num; i++)        //creating a list of heaps
    {
        heap[i] = newHeap();
    }

    printf("Heaps are indexed from 1 to %d.\n", num);
    if(test == true){
        tester(heap);
    }
    else{
        while(choice != -1)
        {
            printf("Choose a heap between index 1 and %d to do operations on. To exit, enter -1.", num);
            char *heapchoice = "";
            choice = inputMachine(heapchoice);
            while(job != 8)
            {   
                if(choice < -1|| choice == 0 || choice > num)     //make sure that the chosen index exists
                {
                    printf("Invalid choice.\n");
                    break;
                }
                printf("\nHeap %d chosen.\n", choice);
                
                printf("Choose an operation to conduct on the selected heap:\n1 - Insert         5 - Decrease Key \n2 - Delete         6 - Print Heap\n3 - Extract Min    7 - Print Minimum\n4 - Merge Heaps    8 - Exit\n ");
    operations: printf("Enter your choice: ");
                char *operationchoice = "";
                job = inputMachine(operationchoice);

                switch (job)
                {
                case 1: ;               //Insert node
                    int value;
                    char *insertNum = "Enter the number you want to insert: ";
                    value = inputMachine(insertNum);
                    insert(heap[choice], value);
                    printf("\n Inserted %d into the heap.", value);
                    break;

                case 2: ;               //Delete node
                    int *success = (int*)malloc(sizeof(int));
                    *success = 0;
                    value  = inputMachine("Enter the value you want to delete: ");

                    if(heap[choice]->min != NULL){                      //if heap not empty, delete
                        delete(heap[choice], value, success);
                    }

                    if(heap[choice]->min != NULL && *success == 1){     //delete successful
                        printf("Value was deleted.\n");
                    }
                    else{
                        printf("Value doesn't exist.\n");
                    }
                    break;
                
                case 3: ;               //Extract minimum node
                    if(heap[choice]->min != NULL)
                    {
                        value = extractMin(heap[choice]);
                        printf("The minimum extracted was%d\n", value);
                    }
                    else if(heap[choice]->min == NULL){
                        printf("Heap is empty\n");
                    }
                    else{
                        printf("Error");
                    }
                    break;
                
            label4: case 4: ;        //Merge heaps
                    value = inputMachine("Enter the heap index you want to merge with the current heap. To cancel, enter -1: ");
                    if(value >= 0 && value < num)
                    {
                        heap[choice] = mergeHeaps(heap[choice], heap[value]);
                        printf("Heaps %d and %d have been merged.\n", choice, value);
                    }
                    else{
                        printf("Invalid input. Please enter a positive integer value which is a valid heap index.\n");
                        goto label4;
                    }
                    break;

                case 5: ;                //Decrease key
                    int *done = (int*)malloc(sizeof(int));
                    *done = 0;
                    int newValue;
                    value = inputMachine("Enter value of node you want to change: ");
                    newValue = inputMachine("Enter new value: ");
                    
                    if(heap[choice]->min != NULL){
                        findNode(heap[choice], heap[choice]->min, value, newValue, done);
                    }
                    else{
                        printf("Heap empty");
                    }
                    if(heap[choice]->min != NULL && *done == 1 && newValue <= value){
                        printf("%d was changed to %d\n", value, newValue);
                    }
                    else if(newValue <= value){
                        printf("Value not present\n");
                    }
                    break;

                case 6: ;               //print the heap
                    if(heap[choice]->min != NULL)
                    {
                        char s[100] = "";
                        printHeap(heap[choice]->min, s, 0);
                    }
                    else{
                        printf("Heap is empty");
                    }
                    break;

                case 7: ;               //print the minimum element
                    if(heap[choice]->size > 0){
                        printf("The minimum element is %d\n", heap[choice]->min->value);
                    }
                    else{
                        printf("Heap is empty");
                    }
                    break;

                case 8:                 //Exit
                    printf("Exiting");
                    break;

                default:
                    printf("Enter a valid input.\n");
                    goto operations;
                }
            }
            job = 0;
        }
    }
}