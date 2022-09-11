#include <stdio.h>
#include <stdlib.h>

typedef struct No{ 
    int item;
    int size;
    struct No *father;
    struct No *left;
    struct No *right;
}No;

typedef No* Tree;

Tree createTree(){
    Tree A = NULL;
    return A;
}

void valuee(Tree *A, int value){
    No** change;
    No* pass;
    No* news = malloc(sizeof(No));
    news->item = value*2;

    *A = news;
    pass = (*A)->right;
}

int main(){
    Tree A = createTree();
    valuee(&A, 5);
    return 0;
}