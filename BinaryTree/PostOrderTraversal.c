#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
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

void PostOrder(struct node* root)
{
    if(root != NULL)
    {
        int top = -1;
        struct node* stack[MAX];
        bool flag[MAX];
        stack[++top] = root;
        flag[top] = false;

        while(top >= 0)
        {
            if(flag[top] == true)
            {
                printf("%d ",stack[top]->data);
                top--;
            }
            else
            {
                root = stack[top--];
                stack[++top] = root;
                flag[top] = true;
                if(root->right)
                {
                    stack[++top] = root->right;
                    flag[top] = false;
                }
                if(root->left)
                {
                    stack[++top] = root->left;
                    flag[top] = false;
                }
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

    PostOrder(root);
    printf("\n");
    
    return 0;
}