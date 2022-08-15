#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct No{
    struct No *right;
    struct No *left;
    int value;
} No;

typedef No* Tree;

Tree EmptyTree(){
    Tree A = NULL;
    return A;
}

Tree createTree(int value, Tree A, Tree B){
    Tree new = malloc(sizeof(No));
    new->value = value;
    new->left = A;
    new->right = B;
    return new;
}

void showTreeLRRo(Tree A){
    if(A != NULL){
        showTreeLDR(A->left);
        showTreeLDR(A->right);
        printf("%d ", A->value);
    }
}

void showTreeRLRo(Tree A){
    if(A != NULL){
        showTreeLDR(A->right);
        showTreeLDR(A->left);
        printf("%d ", A->value);
    }
}

void showTreeRoLF(Tree A){
    if(A != NULL){
        printf("%d ", A->value);
        showTreeLDR(A->right);
        showTreeLDR(A->left);
    }
}

void showTreeLevel(Tree A){
    if(A == NULL) printf("Empty Tree");
    else{
        Queue A = createQueue(); No* aux = A; 
        A = insertQueue(A, aux);
        do{
            printf("%d ", aux->value);
            A = removeQueue(A);
            if(aux->left != NULL) A = insertQueue(A, aux->left);
            if(aux->right != NULL) A = insertQueue(A, aux->right);
        }while(!emptyQueue(A));
    }
}