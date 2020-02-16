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

void PostOrder(struct node* root)
{
    if(root != NULL)
    {
        PostOrder(root->left);
        PostOrder(root->right);
        printf("%d ",root->data);
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

    PostOrder(root);
    printf("\n");
    
    return 0;
}