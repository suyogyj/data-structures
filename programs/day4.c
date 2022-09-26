#include <stdio.h>

int main(int argc, char **argv){

    int x = 2;
    int y = 9;
    char str[] = "Tujhi aai (gay) :)";
    x = (y=2)*3;
    printf("x = %d, y = %d\n", x, y);
    printf("%s", str);
    return 0;
}
