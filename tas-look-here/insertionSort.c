#include <stdio.h>
#include <stdlib.h>


void insertionSort(int arr[], int size){

    int i,j;

    for(i = 0; i < size; i++)
    {
        int k = arr[i];
        j = i-1;

        while(k < arr[j] && j >= 0)
        {
            arr[j+1] = arr[j];
            --j;
        }
        arr[j + 1] = k;

    }

}
void printArray(int arr[], int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d \n", arr[i]);
    }
}


int main()
{

    int num, b, c;
    printf("Enter size of array to be sorted: ");
    scanf("%d", &num);

    int a[num];

    for(b = 0; b < num; b++)
    {
        printf("Enter number: ");
        scanf("%d", &c);
        printf("\n");
        a[b] = c;
    }

    int size = (sizeof(a) / sizeof(a[0]));

    printf("Array before sorting: \n");

    printArray(a, size);

    insertionSort(a, size);

    printf("Array after sorting: \n");

    printArray(a, size);
}
