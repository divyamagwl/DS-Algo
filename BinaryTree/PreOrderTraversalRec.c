#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node* left, *right;
};

struct node* NewNode(int data)
{
    struct node* temp = malloc(sizeof(struct node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void PreOrder(struct node* root)
{
    if(root != NULL)
    {
        printf("%d ",root->data);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

int main()
{
    struct node* root = NewNode(1);
    root->left = NewNode(2);
    root->right = NewNode(3);
    root->left->left = NewNode(4);
    root->left->right = NewNode(5);
    root->right->left = NewNode(6);
    root->right->right = NewNode(7);

    PreOrder(root);
    printf("\n");
    
    return 0;
}