#include <stdlib.h>
#include <stdio.h>

//this program adds all the elements (except every third one) from the original list and sorts the new list. 
//Then it prints the first k elements from the sorted list. 

void kSmallestAmongUntouched(int* a, int k, int n)
{
    int i;
    int j = 0;
    int newArrExtraSize = n/3;  //to prevent creating an array that is larger than needed. 
    int arr[n - newArrExtraSize];

    //exit if k is greater than size of list 
    if(k > n - newArrExtraSize)
    {
        printf("k is bigger than length of list.");
        exit(0);
    }

    //adds all elements (except for every third) in a new list
    for(i = 0; i < n; i++)
    {
        if((i+1) % 3 == 0)
        {
            continue;
        }
        arr[j] = a[i];
        j++;
    }
    
    for(i = 0; i < n - newArrExtraSize; i++)
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


    for(int i = 0; i < k; i++)
    {
        printf("%d \n", arr[i]);
    }
}



int main()
{
   int a[] = {12, 4};
   int n = sizeof(a)/sizeof(a[1]);
   kSmallestAmongUntouched(a, 2, n);
}