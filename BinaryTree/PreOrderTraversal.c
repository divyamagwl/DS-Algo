#include<stdio.h>
#include<stdlib.h>
#define MAX 100000

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
        int top = -1;
        struct node* stack[MAX];
        stack[++top] = root;

        while(top >= 0)
        {
            printf("%d ",stack[top]->data);
            root = stack[top--];
            if(root->right)
            {
                stack[++top] = root->right;
            }
            if(root->left)
            {
                stack[++top] = root->left;
            }
        }
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