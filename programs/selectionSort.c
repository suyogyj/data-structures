#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

void selectionSort(int values[], int n){

    int i, x, min;

    for(i = 0; i < n-1; i++)
    {
        min = i;
        for(x = i + 1; x < n; x++)
        {
            if(values[x] < values[min])
            {
                min = x;
            }

            if(min != i)
            {
                swap(&values[min], &values[i]);
            }
        }

    }
}

void print(int values[], int size)
{
    int temp;
    for(temp = 0; temp < size; temp++)
    {
        printf("%d", values[temp]);
        printf("\n");
    }
}

int main()
{
    int values[] = {7, 5, 82, 2, 102, 1};
    int n =  (sizeof(values)/sizeof(values[0]));

    selectionSort(values, n);

    print(values, n);
    return 0;

}



