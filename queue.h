#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    Node* next;
    void* value;
}Node;

typedef Node* Queue;

Queue createQueue(){
    Queue A = NULL;
    return A;
}

Queue insertQueue(Queue A, void* value){
    Node* newer = (Node *) malloc(sizeof(Node));

    if(newer != NULL){
        newer->next = NULL;
        newer->value = value;
        if(A == NULL) A = newer;

        if(A != NULL){
            Node* aux = A;
            while(aux->next != NULL){
                aux = aux->next;
            }
            aux->next = newer;
        }
    }

    return A;
}

Queue removeQueue(Queue A){
    if(A != NULL){
        Node* aux = A;
        A = A->next;
        free(aux);
    }

    return A;
}

void clearQueue(Queue A){

    while(A != NULL){
        removeQueue(A);
    }
}

bool emptyQueue(Queue A){
    if(A == NULL) return true;
    return false;
}
