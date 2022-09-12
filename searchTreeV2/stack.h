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
    Node* aux, *pre;

    if(A != NULL){
        if(A->next == NULL){
            aux = A;
            A = NULL;
            free(aux);
        }else{
            aux = A;
            while(aux->next != NULL){
                pre = aux;
                aux = aux->next;
            }
            pre->next = NULL;
            free(aux);
        }
    }

    return A;
}

Stack popQueue(Stack A){
    if(A != NULL){
        Node* aux = A;
        A = A->next;
        free(aux);
    }
    return A;
}

Stack insertQueue(Stack A, void* item){
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

int amountElements(Stack A){
    int amount = 0;

    if(A != NULL){
        Node* aux = A;
        do{
            amount++;
            aux = aux->next;
        }while(aux != NULL);
    }

    return amount;
}