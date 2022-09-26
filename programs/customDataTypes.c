#include <stdio.h>
#include <stdlib.h>

struct nodeType{
        int value;
        struct nodeType * next;

};

typedef struct nodeType Node;

int main(int argc, char **argv){
    int i,val;
    Node * head = NULL;
    Node * temp = NULL;

    i = 0;
    scanf("%d", &val);
    while(val>0){
        temp = malloc(sizeof(Node));
        temp->value = val;
        temp->next = NULL;
        // if this is the first time
        // or else
        i = i+1;
        scanf("%d", &val);

    }
}
