#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv){

//    int x = 2;
//    int y = 9;
//    char str[] = "Tujhi aai (gay) :)";
//    x = (y=2)*3;
//    printf("x = %d, y = %d\n", x, y);
//    printf("%s", str);



//    const int x = 5;
//    int * p = &x;
//    *p = 6;
//    printf("x = %d\n",x);
//    printf("*p = %d", *p);


//    const char * string = "Can't touch this";
//    string = "can't touch this either heheheheheheheheheeheheheheheheehehehehe";
//    printf("%s\n", string);


    int * a;
    int i, n, val;
    n = 3;
    a = (int *) malloc(n * sizeof(int));

    i = 0;
    scanf("%d", &val);
    while(val>0){

        a[i] = val;
        i = i+1;
        if(i >=n) {
            n = n*2;
            a = (int *) realloc(a,n * sizeof(int));
        }

        scanf("%d", &val);

    }

    n = i;
    a = realloc(a, n * sizeof(int));

    for(i = 0; i <n; i++){

        printf("%d", a[i]);

    }

    printf("\n\nDone!\n");

    return 0;
}
