#include <stdio.h>
#include <stdlib.h>

void advancedFizzBuzz(int* a, int m, int *b, int nb, int *f, int nf)
{
    int fizz, buzz;
    int i,j,k;
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < nf; j++)
        {
            if(a[i] % f[j] == 0)
            {
                fizz = 1;
                break;
            }
        }

        for(k = 0; k < nb; k++)
        {
            if(a[i] % b[k] == 0)
            {
                buzz = 1;
                break;
            }
        }

        if(fizz == 1 && buzz == 0)
        {
            printf("fizz\n");
        }

        else if(fizz == 0 && buzz == 1)
        {
            printf("buzz\n");
        }

        else if (fizz == 1 && buzz == 1)
        {
            printf("fizzbuzz\n");
        }

        else
        {
            printf("%d\n", a[i]);
        }
        fizz = 0;
        buzz = 0;
    }
}

int main()
{   
    int a[] = {1,2,3,4,5,6,7,8,9,10};
    int m = 10;
    int f[] = {3,5};
    int b[] =  {11, 13};
    int nf = 2;
    int nb = 2;
    advancedFizzBuzz(a, m, b, nb, f, nf);
}