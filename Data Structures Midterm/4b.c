#include <stdio.h>
#include <stdlib.h>

struct heap
{
        int num;
        int left;
        int right;
};

typedef struct heap* HeapAddress;

void returnSmallestNum(int *maxHeap, int n)
{
	int arr[500] = {};

	for(int i = 0;i < n; i++)
    {
		int maxNum = extractMax(maxHeap, n-i);
		arr[i] = maxNum;
	}

	printf("%d", arr[n-1]);
	
}

void swap(int* a, int* b)
{
        int tmp = *a;
        *a = *b;
        *b = tmp;
}

void heapify(int* x, int size, int i)       //from my github
{

        int temp = i;
        int left = (2*i)+1;
        int right = (2*i)+2;

        if(left<size && x[left] > x[temp])
        {
                temp = left;
        }
        if(right< size && x[right] > x[temp])
        {
                temp = right;
        }

        if(temp != i)
        {
                swap(&x[i], &x[temp]);
                heapify(x, size, temp);
        }
}

int extractMax(int* x, int n)   //CITATION: geeksforgeeks.org/binary-heap/
{
        int max = x[0];
        x[0] = x[n-1];
        x[n-1] = max;
        n = n-1;
        heapify(x,n,0);

        return max;
}

int main()
{
        int a[] = {37,22,17,15,12,7,8};
        int size = sizeof(a)/sizeof(a[0]);
        returnSmallestNum(a, size);
}
