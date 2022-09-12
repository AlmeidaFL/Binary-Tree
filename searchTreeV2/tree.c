#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

typedef struct Noded{
    int key;
    struct Noded* father;
    struct Noded* left;
    struct Noded* right;
}Noded;

typedef Noded* Tree;

Tree insertElement(Tree A, int value);
Tree insertNoded(Tree A, Noded* newNoded);
int getHeight(Tree A);
Tree removeTree(Tree A, Noded * item);
Noded* getMaximumTree(Tree A);
Noded* getMinimum(Tree A);
Noded* comumAncestor(Tree tree, Noded* A, Noded* B);
Noded* comumAncestorR(Tree tree, Noded* A, Noded* B);
Tree removeRoot(Tree A);
Tree freverter(Tree A);
Tree removeNoded(Tree A, int value);
void empty(Tree A);
Noded* select(Tree A, int value);
int countBigger(Tree A, int value);
int countBigger(Tree A, int value);

int main(){
    Tree A = NULL;
    Noded* test;
    A = insertElement(A, 5);
    A = insertElement(A, 9);
    A = insertElement(A, 1);
    A = insertElement(A, 10);
    A = insertElement(A, 2);
    A = insertElement(A, 6);
    A = insertElement(A, 3);

    test = select(A, 10);
    printf("\nNoded test = %d", test->key);

    int count = countBigger(A, 3);
    int qtdNos = getHeightNotR(A);


    return 0;
}

Tree insertElement(Tree A, int value){
    Noded* newNoded = malloc(sizeof(Noded));

    if(newNoded != NULL){
        newNoded->left = NULL; newNoded->right = NULL; newNoded->key = value;
        if(A == NULL){ //There's no item in the tree
            newNoded->father = NULL; A = newNoded;
        }else{ //There's item in the tree
            Noded* aux = A, *pre;
            while(aux != NULL){ //Serching newNoded's father
                pre = aux;
                if(aux->key > value) aux = aux->left;
                else aux = aux->right;
            }
            if(pre->key > value) pre->left = newNoded;
            else pre->right = newNoded;
            newNoded->father = pre;
        }
    }

    return A;
}

Tree insertNoded(Tree A, Noded* newNoded){
    Tree newTree = A;
    
    newNoded->left = NULL; newNoded->right = NULL;
    if(A == NULL){
        newTree = newNoded;
    }else{
        Noded* aux = A, *pre; 
        while(aux != NULL){
            pre = aux;
            if(aux->key > newNoded->key) aux = aux->left;
            else aux = aux->right;
        }
        if(pre->key > newNoded->key) pre->left = newNoded;
        else pre->right = newNoded;
    }
    return newTree;
}

int getHeight(Tree A){
    int height, hLeft, hRight;
    Noded * temp = A;
    
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

Tree removeTree(Tree A, Noded * item){
    Noded * temp, *father, *son;

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

Noded* getMaximumTree(Tree A){
    Noded* maximum = A;
    if(A != NULL){
        while(maximum->right != NULL){
            maximum = maximum->right;
        }
    }
    return maximum;
}

Noded* getMinimum(Tree A){
    Noded* minimum = A;
    if(A != NULL){
        while(minimum->left != NULL){
            minimum = minimum->left;
        }
    }
    return minimum;
}

Noded* comumAncestor(Tree tree, Noded* A, Noded* B){
    Noded* ancestor = NULL;
    if(tree != NULL){
        Noded* root = tree;
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

Noded* comumAncestorR(Tree tree, Noded* A, Noded* B){
    Noded* ancestor = NULL;
    if(tree != NULL){
        Noded* root = tree;
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
    Noded* newRoot = NULL;
    if(A != NULL){
        if(A->left != NULL && A->right != NULL){ // Two sons
            Noded *newRoot = getMinimum(A->right);
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
        Noded* aux = A->left;
        A->left = A->right;
        A->right = A->left;
        freverter(A->right);
        freverter(A->left);
    }
    return A;
}
Tree removeNoded(Tree A, int value){
    if(A != NULL){
        Noded* aux = A;
        while((aux != NULL) && (aux->key != value)){
            if(aux->key > value) aux = aux->left;
            else aux = aux->right;
        }

        if(aux != NULL){
            Noded* father = aux->father;
            Noded* son = removeRoot(aux);
            son->father = father;
            if(father->key > son->key) father->left = son;
            else father->right = son;
        }
    }
    return A;
}
void empty(Tree A){
    Noded *root = A;
    
    if(root != NULL){
        empty(root->left);
        empty(root->right);
        free(root);
    }
}
/*
void reverse(Tree A){
    Noded* temp;
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
Noded* selectTree(Tree A, int value){
    if((A != NULL) && (value > 0)){
        int count = 0;
        Stack stack = createStack();
        Noded* aux = A;
        bool last = false;
        do{
            Noded* minimum;
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
                aux = (Noded *) getTop(stack); stack = popStack(stack);
                last = true;
            }
        }while((count < value) && (!emptyStack(stack)));
    }
}
*/

Noded* select(Tree A, int value){
    Noded* aux = A, *temp;
    int count = 0;
    Stack stack;
    bool veri = false;

    if(A != NULL){
        stack = createStack();
       
        do{
            while(aux != NULL && count < value){
                stack = pushStack(stack, aux);
                aux = aux->left;
            }

            if(emptyStack(stack) == false && count < value){
                aux = getTop(stack); 
                stack = popStack(stack);
                temp = aux;
                aux = aux->right;  
                count ++;
            }else {
                veri = true;
            }
             
        }while(veri == false);        
    }
    return temp;
}

int countBigger(Tree A, int value){
    int count = 0;
    if(A != NULL){
        Stack stack = createStack();
        Noded* aux = A;
        bool final = false;
        do{
            while(aux != NULL){
                stack = pushStack(stack, aux);
                aux = aux->left;
            }

            if(!emptyStack(stack)){
                aux = getTop(stack); stack = popStack(stack);
                if(aux->key > value) count++;
                aux = aux->right;
            }else final = true;
        }while(!final);
    }

    return count;
}

int getHeightNotR(Tree A){
    int height = 0;

    if(A != NULL){
        int amountNodes;
        Stack queue = createStack();
        queue = insertQueue(queue, A);
        bool final = false;

        do{
            amountNodes = amountElements(queue);
            if(amountNodes == 0) final = true;
            else height++;

            while(amountNodes > 0){
                Noded* aux = getTop(queue); 
                queue = popQueue(queue);
                if(aux->left != NULL){
                    queue = insertQueue(queue, aux->left);
                }if(aux->right != NULL){
                    queue = insertQueue(queue, aux->right);
                }
                amountNodes--;
            }
        }while(!final);
    }

    return height;
}