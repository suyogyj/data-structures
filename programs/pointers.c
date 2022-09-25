#include <stdio.h>
#include <stdlib.h>

int main(){

	int x = 3;
	int *y;
	y = &x;
	printf("%d \n",x);
    printf("%p", y);
	return 0;

}
