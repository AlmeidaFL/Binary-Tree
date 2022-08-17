#include <stdio.h>
#include <stdlib.h>
#include "../queue.h"
#include <time.h>


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
        showTreeLRRo(A->left);
        showTreeLRRo(A->right);
        printf("%d ", A->value);
    }
}

void showTreeRLRo(Tree A){
    if(A != NULL){
        showTreeRLRo(A->right);
        showTreeRLRo(A->left);
        printf("%d ", A->value);
    }
}

void showTreeRoLF(Tree A){
    if(A != NULL){
        printf("%d ", A->value);
        showTreeRoLF(A->right);
        showTreeRoLF(A->left);
    }
}

void showTreeLevel(Tree A){
    if(A == NULL) printf("Empty Tree");
    else{
        Queue queue = createQueue();
        queue = insertQueue(queue, A);
        do{
            No* aux = (No *) firstQueue(queue);
            printf("%d ", aux->value);
            queue = removeQueue(queue);
            if(aux->left != NULL) queue = insertQueue(queue, aux->left);
            if(aux->right != NULL) queue = insertQueue(queue, aux->right);
        }while(!emptyQueue(queue));
    }
}


int treeHeight(Tree A){
    int heightA = -1, heightB = -1;

    if(A != NULL){
        if(A->left != NULL) heightA = treeHeight(A->left);
        if(A->right != NULL) heightB = treeHeight(A->right);
        if(heightB > heightA) heightA = heightB;
        heightA++;
    }
    
    return heightA;
}

int amountNodes(Tree A){
    int amount = 0;

    if(A != NULL){
        amount += amountNodes(A->left);
        amount += amountNodes(A->right);
        amount++;
    }
    

    return amount;
}

Tree buildBalancedTree(int amountNodes){
    Tree tree = malloc(sizeof(Node));
    
    if(tree != NULL && amountNodes > 0){
        int number = rand()%100;
        tree->value = number;
        int n1 = amountNodes/2; int n2 = amountNodes - n1;
        tree->left = buildBalancedTree(n1);
        tree->right = buildBalancedTree(n2);
    }

    return tree;
}

int amountLeafs(Tree A){
    int amount = 0;

    if(A != NULL){
        if(A->left == NULL && A->right == NULL) amount++;
        else{
            amount += amountLeafs(A->left);
            amount += amountLeafs(A->right);
        }
    }

    return amount;
}

No* searchNode(Tree A, int value){
    No* aux;

    if(A != NULL){
        Queue queue = createQueue(); bool find = false;
        queue = insertQueue(queue, A);
        do{
            aux = (No *) firstQueue(queue);
            if(aux->value == value) find = true;
            else{
                queue = removeQueue(queue);
                if(aux->left != NULL) queue = insertQueue(queue, aux->left);
                if(aux->right != NULL) queue = insertQueue(queue, aux->right);
            }
        }while(!emptyQueue(queue) && !find);

        if(!find) aux = NULL;
    }

    return aux;
}

int main(){
    Tree a,b,c;
    srand(time(NULL)); 
	a = createTree(6,NULL,NULL); 
    b = createTree(3,NULL,NULL);
    c = createTree(5,a,NULL); 
    a = createTree(1,c,b);
    b = createTree(7,NULL,NULL); 
    c = createTree(4,NULL,b);
	b = createTree(2,a,c);

    showTreeLevel(b);
    printf("\nTree height: %d\n", treeHeight(b));
    printf("\nAmount nodes: %d\n", amountNodes(b));
    printf("\nAmount leaf: %d\n", amountLeafs(b));

    printf("\nFinded: %d", searchNode(b, 7)->value);

    
    return 0;
}