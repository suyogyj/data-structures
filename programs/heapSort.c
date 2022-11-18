#include <stdio.h>

//build max heap using heapsort

struct node
{
    int value;
    struct node* nextP
};

typedef struct node listNode;

void swap(int* x, int* y)
{
    int temp  = *x;
    *x = *y;
    *y = temp;
}

void printArray(int arr[], int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
}

void heapify(int arr[], int size, int i)
{
    int temp = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left<size && arr[left] > arr[temp])
    {
        temp = left;
    }

    if(right<size && arr[right] > arr[temp])
    {
        temp = right;
    }


    if(temp != i)
    {
        swap(&arr[i], &arr[temp]);
        heapify(arr, size, temp);
    }

}

void heapSort(int arr[], int i)
{
    for(int j = (i/2) - 1; j >= 0; j--)
    {
        heapify(arr, i, j);
    }
    for(int j = i - 1; j >= 0; j--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr,i,0);
    }
}

int main()
{
    int arr[] = {1,2,3,4,5,6};
    int size = sizeof(arr)/sizeof(arr[0]);
    heapify(arr, size, 0);
    printArray(arr, size);
    printf("\n");
    heapSort(arr, size);
    printArray(arr,size);
}