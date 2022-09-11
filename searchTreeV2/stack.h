#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    struct Node* next;
    void* item;
}Node;

typedef Node* Stack;

Stack createStack(){
    Stack A = NULL;
    return A;
}

Stack pushStack(Stack A, void* item){
    Node* newNode = (Node *) malloc(sizeof(Node));

    if(newNode != NULL){
        newNode->next = NULL; newNode->item = item;
        if(A == NULL){
            A = newNode;
        }else{
            Node* aux = A;
            while(aux->next != NULL) aux = aux->next;
            aux->next = newNode;
        }
    }

    return A;
}

Stack popStack(Stack A){
    if(A != NULL){
        Node* aux = A;
        while(aux->next != NULL) aux = aux->next;
        aux = NULL;
        free(aux);
    }

    return A;
}

void* getTop(Stack A){
    void* top = NULL;
    if(A != NULL){
        Node* aux = A;
        while(aux->next != NULL) aux = aux->next;
        top = aux->item;
    }
    return top;
}

bool emptyStack(Stack A){
    bool empty = false;
    if(A == NULL) empty = true;
    return empty;
}