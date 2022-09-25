#include <stdio.h>
#include <stdlib.h>

int pointer(){

    int x = 4;
    int *y;
    y = &x;

    printf("%d",*y);

    return 0;
}

