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

/* void Enqueue(struct node* Queue[], struct node* root, int* tail)
{
    *tail++;
    Queue[*tail] = root;
}

struct node* Dequeue(struct node* Queue[], int* head)
{
    *head++;
    return(Queue[*head - 1]);
} */

void LevelOrder(struct node* root)
{
    struct node* Queue[MAX];
    int head = 0, tail = 0;
    Queue[tail] = root;
    while(head <= tail)
    {
        root = Queue[head];
        head++;
        printf("%d ",root->data);
        if(root->left)
        {
            Queue[++tail] = root->left;
        }
        if(root->right)
        {
            Queue[++tail] = root->right;
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

    LevelOrder(root);
    printf("\n");
    
    return 0;
}