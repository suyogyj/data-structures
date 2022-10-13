#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};


void printLinkedList(struct node *p){

    while(p != NULL){
        printf("%d \n", p->value);
        p  = p->next;
    }
}

int main() {
    int x,y,z;
    printf("Enter a number");
    scanf("%d", &x);
    printf("Enter a number");
    scanf("%d", &y);
    printf("Enter a number");
    scanf("%d", &z);


    struct node *head;
    struct node *one = NULL;
    struct node *two = NULL;
    struct node *three = NULL;

    one = malloc(sizeof(struct node));
    two = malloc(sizeof(struct node));
    three = malloc(sizeof(struct node));

    one->value = x;
    two->value = y;
    three->value = z;

    one->next = two;
    two->next = three;
    three->next = NULL;

    head = one;
    printLinkedList(head);


}
