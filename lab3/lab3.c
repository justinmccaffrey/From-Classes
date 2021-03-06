#include <stdio.h>
#include <stdlib.h>
struct btnode{
    int data;
    struct btnode *left;
    struct btnode *right;
};

struct btnode *createNode(int data){
    struct btnode * newNode=(struct btnode *)malloc(sizeof(struct btnode));
    newNode->data=data;
    newNode->left=NULL;
    newNode->right=NULL;
    return(newNode);
}
struct btnode *insertNode(struct btnode* node,struct btnode* root){
    if(root==NULL){
        root=node;
    }
    else if(node->data<root->data){
        if(root->left==NULL){
            root->left=node;
        }
        else{
            insertNode(node,root->left);
        }
    }
    else{
        if(root->right==NULL){
            root->right=node;   
        }
        else{
            insertNode(node,root->right);
        }
    }
    return root;
}
inOrder(struct btnode* root){
    if(root==NULL) return;
    inOrder(root->left);
    printf("%i,",root->data);
    inOrder(root->right);
}
preOrder(struct btnode* root){
    if(root==NULL) return;
    printf("%i,",root->data);
    preOrder(root->left);
    preOrder(root->right);
}
int sizeTree(struct btnode* root){
    if(root==NULL) return 0;
    int size=1;
    size+=sizeTree(root->left);
    size+=sizeTree(root->right);
    return size;
}
int maxHeight(struct btnode* root){
    if(root==NULL) return 0;
    int maxLeft,maxRight;
    maxLeft=maxHeight(root->left);
    maxRight=maxHeight(root->right);
    if(maxLeft>maxRight){
        return (maxLeft+1);
    }
    else{
        return (maxRight+1);
    }
}
int minValue(struct btnode* root){
    if(root->left==NULL){
        return root->data;
    } 
    return minValue(root->left);
}
freeTree(struct btnode* root){
    if(root!=NULL){
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
int main()
{
    struct btnode* root=NULL;
    int x=0,value,size,i;
    printf("%s","Enter the number of nodes in the tree: ");
    scanf("%d",&size);
    for(i=0;i<size;i++){
        printf("%s","Enter an integer: ");
        scanf("%i",&value); 
        root=insertNode(createNode(value),root);
    }
    if(size>0){
    do{
    printf("%s","Enter 0 to quit\n1 to print inorder traversal\n2 to print preorder traversal\n3 to print the size of the tree\n4 to print the max height of the tree\n5 to print the minimum value in the tree :");
    scanf("%d",&x);
    switch (x){
    case 1 :
        inOrder(root);
        break;
    case 2 :
        preOrder(root);
        break;
    case 3 :
        printf("%i\n",sizeTree(root));
        break;
    case 4 :
        printf("%i\n",maxHeight(root));
        break;
    case 5 :
        printf("%i\n",minValue(root));
        break;
    default ://exit
        printf("%s\n","exiting..");
        x=0;
    if(root!=NULL){
        freeTree(root);
    }
    }
    }while(x>0);
    }
    return 0;

}





