#include <stdlib.h>
#include <stdio.h>


//from my selectionsort submission on github
int* sortEveryThirdElement(int* a, int n)
{
    int i, x, min;

    for(i = 2; i < n-1; i+=3)
    {
        min = i;
        for(x = i + 3; x < n; x +=3)
        {
            if(a[x] < a[min])
            {
                min = x;
            }  
        }
        if(min != i)
        {
            int temp = a[min];
            a[min] = a[i];
            a[i] = temp;
        }

    }
    return a;
}

void print(int values[], int size)
{
    int temp;
    for(temp = 0; temp < size; temp++)
    {
        printf("%d\n", values[temp]);
    }
}


int main()
{
    int values[] = {10, 2, 5, 1 ,3, 4 ,6 ,8, 7,9};
    int n = (sizeof(values)/sizeof(values[0]));

    int* b = sortEveryThirdElement(values, n);

    print(b, n);
}