#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

struct node{
    int data;
    struct node* link;
};

void push(struct node** head, int data)
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->link = (*head);
    (*head) = new_node;
}

void circular(struct node** head, int index)
{
    struct node* new_node = (struct node*) malloc(sizeof(struct node)); 
    struct node* last_node = (struct node*) malloc(sizeof(struct node)); 
    new_node->link = (*head);
    last_node->link = (*head);

    while(last_node->link != NULL)
    {
        last_node = last_node->link;
    }

    for(int i = 0; i<index+1; i++)
    {
        new_node = new_node->link;
    }

    last_node->link = new_node;
}

void printList(struct node *node) 
{
    int excess = 0; 
    while (node != NULL && excess<25) 
    { 
        printf("%d--->", node->data); 
        node = node->link;
        excess ++; 
    }
    printf("NULL\n"); 
}

bool FloydCycle(struct node** head)
{
    struct node* slow = (*head);
    struct node* fast = (*head);

    while(fast != NULL)
    {
        slow = slow->link;
        fast = fast->link;

        if(fast != NULL)
            fast = fast->link;
        else
            return false;

        if(fast == slow)
            return true;
    }
    return false;
}

int main()
{
    struct node* head = NULL; 
  
    push(&head, 7);     
    push(&head, 1); 
    push(&head, 10); 
    push(&head, 5); 
    push(&head, 8); 
    push(&head, 6); 

    printList(head);
    
    if(FloydCycle(&head))
        printf("Yes, it is a circular linked list\n");
    else    
        printf("No, it is not a circular linked list\n");

    circular(&head,2);

    printList(head);

    if(FloydCycle(&head))
        printf("Yes, it is a circular linked list\n");
    else    
        printf("No, it is not a circular linked list\n");

    return 0;
}