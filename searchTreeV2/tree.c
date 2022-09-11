#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

typedef struct Node{
    int key;
    struct Node* father;
    struct Node* left;
    struct Node* right;
}Node;

typedef Node* Tree;

Tree insertElement(Tree A, int value);
Tree insertNode(Tree A, Node* newNode);
int getHeight(Tree A);
Tree removeTree(Tree A, Node * item);
Node* getMaximumTree(Tree A);
Node* getMinimum(Tree A);
Node* comumAncestor(Tree tree, Node* A, Node* B);
Node* comumAncestorR(Tree tree, Node* A, Node* B);
Tree removeRoot(Tree A);
Tree freverter(Tree A);
Tree removeNode(Tree A, int value);
void empty(Tree A);
Node* select(Tree A, int value);

int main(){
    Tree A = NULL;
    Node* test;
    A = insertElement(A, 5);
    A = insertElement(A, 9);
    A = insertElement(A, 3);

    test = select(A, 3);
    printf("\nNode test = %d", test->key);


    return 0;
}

Tree insertElement(Tree A, int value){
    Node* newNode = malloc(sizeof(Node));

    if(newNode != NULL){
        newNode->left = NULL; newNode->right = NULL; newNode->key = value;
        if(A == NULL){ //There's no item in the tree
            newNode->father = NULL; A = newNode;
        }else{ //There's item in the tree
            Node* aux = A, *pre;
            Node* aux = A, *pre;
            while(aux != NULL){ //Serching newNode's father
                pre = aux;
                if(aux->key > value) aux = aux->left;
                else aux = aux->right;
            }
            if(pre->key > value) pre->left = newNode;
            else pre->right = newNode;
            newNode->father = pre;
        }
    }

    return A;
}

Tree insertNode(Tree A, Node* newNode){
    Tree newTree = A;
    
    newNode->left = NULL; newNode->right = NULL;
    if(A == NULL){
        newTree = newNode;
    }else{
        Node* aux = A, *pre; 
        while(aux != NULL){
            pre = aux;
            if(aux->key > newNode->key) aux = aux->left;
            else aux = aux->right;
        }
        if(pre->key > newNode->key) pre->left = newNode;
        else pre->right = newNode;
    }
    return newTree;
}

int getHeight(Tree A){
    int height, hLeft, hRight;
    Node * temp = A;
    
    if(A != NULL){
        hLeft = getHeight(temp->left) + 1;
        hRight = getHeight(temp->right) + 1;
        
        height = hRight;
        if(hLeft > hRight){
            height = hLeft;
        } 
    }else{
       height = -1; 
    }

    return height;
}

Tree removeTree(Tree A, Node * item){
    Node * temp, *father, *son;

    if((A != NULL) && (item != NULL)){
        if(item->left == NULL && item->right == NULL){
            temp = item;
        
        }else if(item->left != NULL && item->right !=NULL){
            temp = item->left;
            temp = getMaximumTree(temp);
            item->key = temp->key; 

            if(temp->left!= NULL){
                father = temp->father;
                son = temp->left;
                father->right = son;
                son->father = father;
            }
        }else{
            temp = item;
            father = temp->father;
            
            if(item->left != NULL && item->right == NULL){
                item = temp->left;
            }else{
                item = temp->right;            
            }
            if(father->key < item->key) father->right = item;
            else father->left = item;
           
        }
        free(temp);        
    }

    return A;
}

Node* getMaximumTree(Tree A){
    Node* maximum = A;
    if(A != NULL){
        while(maximum->right != NULL){
            maximum = maximum->right;
        }
    }
    return maximum;
}

Node* getMinimum(Tree A){
    Node* minimum = A;
    if(A != NULL){
        while(minimum->left != NULL){
            minimum = minimum->left;
        }
    }
    return minimum;
}

Node* comumAncestor(Tree tree, Node* A, Node* B){
    Node* ancestor = NULL;
    if(tree != NULL){
        Node* root = tree;
        bool stop = false;
        while(!stop){
            if((A->key < root->key) && (B->key < root->key)){
                root = root->left;
            }else if((A->key > root->key) && (B->key > root->key)){
                root = root->right;
            }else stop = true;
        }
        ancestor = root;
    }
    return ancestor;
}

Node* comumAncestorR(Tree tree, Node* A, Node* B){
    Node* ancestor = NULL;
    if(tree != NULL){
        Node* root = tree;
        if((A->key < root->key) && (B->key < root->key)){
            root = comumAncestorR(root->left, A, B);
        }else if((A->key > root->key) && (B->key > root->key)){
            root = comumAncestorR(root->right, A, B);
        }
        ancestor = root;
    }
    return ancestor;
}

Tree removeRoot(Tree A){
    Node* newRoot = NULL;
    if(A != NULL){
        if(A->left != NULL && A->right != NULL){ // Two sons
            Node *newRoot = getMinimum(A->right);
            newRoot->right = A->right;
            newRoot->left = A->left;
            newRoot->father->left = NULL;
            newRoot->father = NULL;
        }
        else{ //One son
            if(A->left == NULL){ 
                newRoot = A->right;
            }else if(A->right == NULL){
                newRoot = A->left;
            }
        }
        free(A);
    }

    return newRoot;
}

Tree freverter(Tree A){
    if(A != NULL){
        Node* aux = A->left;
        A->left = A->right;
        A->right = A->left;
        freverter(A->right);
        freverter(A->left);
    }
    return A;
}
Tree removeNode(Tree A, int value){
    if(A != NULL){
        Node* aux = A;
        while((aux != NULL) && (aux->key != value)){
            if(aux->key > value) aux = aux->left;
            else aux = aux->right;
        }

        if(aux != NULL){
            Node* father = aux->father;
            Node* son = removeRoot(aux);
            son->father = father;
            if(father->key > son->key) father->left = son;
            else father->right = son;
        }
    }
    return A;
}
void empty(Tree A){
    Node *root = A;
    
    if(root != NULL){
        empty(root->left);
        empty(root->right);
        free(root);
    }
}
/*
void reverse(Tree A){
    Node* temp;
    if(A != NULL){
        reverse(A->left);
        reverse(A->right);
        
        temp = A->left;
        A->lef= A->right;
        A->right = temp; 
    }
}
*/

/*
Node* selectTree(Tree A, int value){
    if((A != NULL) && (value > 0)){
        int count = 0;
        Stack stack = createStack();
        Node* aux = A;
        bool last = false;
        do{
            Node* minimum;
            if((aux->left != NULL) && (!last)){
                minimum = aux;
                while(minimum->left != NULL){
                     stack = pushStack(stack, minimum); 
                     minimum = minimum->left;  
                }
                count++;
                aux = minimum;
            }
            if(aux->right != NULL){
                aux = aux->right;
                last = false; //Entra no primerio if
            }
            else if(aux->right == NULL && aux->left == NULL){
                aux = (Node *) getTop(stack); stack = popStack(stack);
                last = true;
            }
        }while((count < value) && (!emptyStack(stack)));
    }
}
*/

Node* select(Tree A, int value){
    Node* aux = A;
    int count = 0;
    Stack stack;
    bool veri = false;

    if(A != NULL){
        stack = createStack();
        do{
            while(aux != NULL && count <= value){
                aux = push(stack, aux);
                aux = aux->left;
            }

            if(emptyStack(stack) == false && count <= value){
                aux = getTop(stack);
                count ++;
            }else {
                veri = true;
            }
        }while(veri == false);        
    }
    return aux;
}
