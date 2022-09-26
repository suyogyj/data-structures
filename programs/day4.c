#include <stdio.h>
#include <stlib.h>
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
    int n = 10;

    a = malloc(n * sizeof(int));
    for(int i = 0; i <n; i++){

        a[i] = i;

    }

    return 0;
}
