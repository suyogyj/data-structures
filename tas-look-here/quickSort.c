#include <stdio.h>
#include <stdlib.h>



void quickSort(int arr[], int low, int high)
{
    if(low<high)
    {
        int index = partition(arr, low, high);
        quickSort(arr, low, index - 1);
        quickSort(arr, index + 1, high);
    }
}

int partition(int arr[], int low, int high)
{
    int pivot  = arr[high];
    int i = low - 1;
    int j;
    for(j = low; j < high; j++)
    {
        if(arr[j] < pivot)
        {
            i++;
            //swap i,j
            swap(&arr[i], &arr[j]);
        }
    }
    //swap i+1, high
    swap(&arr[i+1], &arr[high]);
    return (i+1);

}

void swap(int* x, int* y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

printArray(int array[], int size)
{
    int temp;
    for(temp = 0; temp < size; temp++)
    {
        printf("%d", array[temp]);
        printf("\n");
    }
}

int main()
{
    int num, b, c;
    printf("Enter size of array to be sorted: ");
    scanf("%d", &num);

    int array[num];

    for(b = 0; b < num; b++)
    {
        printf("Enter number: ");
        scanf("%d", &c);
        printf("\n");
        array[b] = c;
    }
    int size = sizeof(array)/sizeof(array[0]);
    printf("Array before sorting:\n");
    printArray(array, size);
    quickSort(array, 0, size - 1);
    printf("Array after sorting:\n");
    printArray(array, size);


}