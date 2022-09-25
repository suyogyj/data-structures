#include <stdio.h>
#include <stdlib.h>

int main(){

	int x = 4;
	int *y;
	int z = 3;
	y = &x;
//    printf("%d \n",x);
//    printf("%p\n", y);
//
//
//    printf("%d\n", *y);
//    printf("%p\n", &x);
//
//    printf("%d\n", z);
//    printf("%p", &z);

    *y = *y+1;
    printf("%d \n",x);

	return 0;

}
