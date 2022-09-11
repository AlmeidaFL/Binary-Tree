#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Lista.h"

typedef struct No{ 
    int item;
    int size;
    struct No *father;
    struct No *left;
    struct No *right;
}No;

typedef No* Tree;

int getItemMinimum(Tree A);
int getItemMaximum(Tree A);
No* obterSeguinte(Tree ap, int y);
No *getMaximum(Tree A);
No *getMinimum(Tree A);
void showTree(Tree A);
void insertTree(Tree* A, int value);
No* findItem(Tree A, int value);
void removeTree(Tree* A, No* son);

Tree createTree(){
    Tree A = NULL;
    return A;
}
/*
void removeTree(Tree* A, No* son){
    if(A != NULL){
        No* item = findItem((*A), son->item);
        if(item != NULL){
            No** father = &(item->father);
            bool left;
            if((*father)->left == item) left = true;
            else left = false;

            if((item->left == NULL) && (item->right == NULL)){ //Leaf
                if(left) (*father)->left = NULL;
                else (*father)->right = NULL;
            }
            else if(item->left == NULL){ //son has item-left null
                if(left) (*father)->left = getItemMaximum(item);
                else (*father)->right = getItemMinimum(item);
            }else if(item->right == NULL){ //son has item-right null
                if(left) (*father)->left = getItemMaximum(item);
                else (*father)->right = getItemMinimum(item);
            }
            
        }
    }
}*/

/*
            if((item->left == NULL) && (item->right == NULL)){ //Leaf
                if((*father)->left->item == item->item) (*father)->left = NULL;
                else (*father)->right = NULL;
            }
            else if(item->left == NULL){
                (*father).
            }

No* findItem(Tree A, int value){
    No* aux = A;
    if(A != NULL){
        No *pre; 
        bool find = false;
        while(aux != NULL && !find){
            pre = aux;
            if(aux->item == value) find = true;
            else{
                if(value < aux->left) aux = aux->left;
                else aux = aux->right;
            }
        }
        if(find) aux = pre;
        else aux = NULL;
    }
    return aux;
}
*/

void insertTree(Tree* A, int value){
    No* son, *aux, **pre;
    son = malloc(sizeof(No));

    if(son != NULL){
        son->left = NULL; son->right = NULL; son->father = NULL; 
        son->item = value; son->size = 1;
        if(*A == NULL) *A = son; 
        else{
            aux = *A;
            while(aux != NULL){
                *pre = aux; (*pre)->size++;
                if(son->item < aux->item) aux = aux->left;
                else aux = aux->right;
            }
            if(son->item < (*pre)->item) (*pre)->left = son; 
            else (*pre)->right = son;
            son->father = *pre;
        }
    }
}

void showTree(Tree A){
    if(A != NULL){
        showTree(A->left);
        printf("%d", A->item);
        showTree(A->right);
    }
}

No *getMinimum(Tree A){
    No* minimum = NULL;
    if(A != NULL){
        minimum = A;
        while (minimum->left != NULL) minimum = minimum->left;
    }
    return minimum;
}

No *getMaximum(Tree A){
    No* maximum = NULL;
    if(A != NULL){
        maximum = A;
        while(maximum->right != NULL) maximum = maximum->right;
    }

    return maximum;
}

No* getNext(Tree A, int value){
    No* next = NULL;
    if(A != NULL){
        No* aux = A;
        while((aux != NULL) && (aux->item != value)){ //Searching the node which contains the value
            if(aux->item > value) aux = aux->left;
            else aux = aux->right;
        }

        if(aux != NULL){
            if(aux->right != NULL){ // If tree has right son
                next = getMinimum(aux->right);
            }else{
                No* son = aux; 
                No *father = aux->father;
                while((father != NULL) && (father->right == son)){
                    son = father;   father = son->father;
                }
                if(father != NULL) next = father;
            }
        }
    }
    return next;
}
int getItemMaximum(Tree A){
    int maximum = -1;
    if(A != NULL){
        No *aux = getMaximum(A);
        maximum = aux->item;
    }
    return maximum;
}

int getItemMinimum(Tree A){
    int maximum = -1;
    if(A != NULL){
        No *aux = getMinimum(A);
        maximum = aux->item;
    }
    return maximum;
}

int main(){
    Tree A = createTree();
    insertTree(&A, 51);
    insertTree(&A, 90);
    insertTree(&A, 60);
    No *aux = obterSeguinte(A, 90);
    if(aux == NULL) printf("OII\n");
    
    return 0;
}