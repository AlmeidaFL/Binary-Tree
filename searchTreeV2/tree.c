#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int key;
    struct Node* father;
    struct Node* left;
    struct Node* right;
}Node;

typedef Node* Tree;

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
        if(pre->father > newNode->key) pre->left = newNode;
        else pre->right = newNode;
    }
    return newTree;
}

int getHeight(Tree A){
    int height, hLeft, hRight;
    Node * temp = A;
    
    if(A != NULL){
        hLeft = getHeight(temp->left) + 1;
        hRight = getTree(temp->right) + 1;
        
        height = hRight;
        if(hLeft > hRight){
            height = hLeft;
        } 
    }else{
       height = -1; 
    }

    return height;
}

Tree remove(Tree A, Node * item){
    Node * temp, *father, *son;

    if((A != NULL) && (item != NULL)){
        if(item->left == NULL && item->right == NULL){
            temp = item;
        
        }else if(item->left != NULL && item->right !=NULL){
            temp = item->left;
            temp = getMaximum(temp);
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

Node* getMaximum(Tree A){
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
        reverter(A->right);
        reverter(A->left);
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