#include <stdio.h>
#include <stdlib.h>

void basicFizzBuzz(int x)
{
    if(x == 0)
    {
        printf("0 \n");
    }
    else if(x % 33 == 0 || x % 39 == 0 || x % 33 == 55 || x % 65 == 0)
    {
        printf("fizbuzz\n");
    }

    else if(x % 3 == 0 || x % 5 == 0)
    {
        printf("fizz\n");
    }

    else if(x % 11 == 0 || x % 13 == 0)
    {
        printf("buzz\n");
    }

    else
    {
        printf("%d \n", x);
    }
}

int main() 
{
    int i;
    for(i = 0; i < 101; i++)
    {
        basicFizzBuzz(i);
    }
}