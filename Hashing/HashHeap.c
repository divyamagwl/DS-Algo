//Design a data structure which supports the following operations efficiently 

//Add an integer x
//delete an integer with maximum frequency - if there are more than one element with the same maximum frequency delete all of them.

#include<stdio.h>
#include<stdlib.h>
#define MAX 4000
#define PRIME 1009
#define swap(a,b) {struct heap (temp); temp = a; a = b; b = temp;}

struct hashtable{
    int data, count, indexH; //indexH -> index of the number in heap
    struct hashtable* next;
    struct hashtable* prev; 
};

struct heap{
    int count;
    struct hashtable* point; //Pointer to hashtable's node
};

//Length of heap 
int length = 0;

//Utility to push data at beginning of the linked list
void push(struct hashtable** head, int data) 
{ 
    struct hashtable* new_node = (struct hashtable*)malloc(sizeof(struct hashtable)); 
  
    new_node->data = data; 
    new_node->count = 1;
    new_node->indexH = length;
  
    new_node->next = (*head); 
    new_node->prev = NULL; 
  
    if ((*head) != NULL) 
        (*head)->prev = new_node; 
  
    (*head) = new_node; 
}

//Utility to delete the given node from doubly linked list
void deleteNode(struct hashtable** head, struct hashtable* del_node)  
{ 
    if (*head == NULL || del_node == NULL)  
        return;  

    if (*head == del_node)
        *head = del_node->next;  

    if (del_node->next != NULL)
        del_node->next->prev = del_node->prev; 

    if (del_node->prev != NULL)
        del_node->prev->next = del_node->next; 

    free(del_node); 
    return; 
} 

//Utility to Bottom Up Heapify the max heap
void BottomUpHeapify(struct heap Heap[], int child)
{
    int parent = (child-1)/2;

    while(parent >= 0 && Heap[parent].count < Heap[child].count)
    {
        swap(Heap[child],Heap[parent]);
        Heap[child].point->indexH = child; //Changing the index to heap from the hastable using the pointer
        Heap[parent].point->indexH = parent; //Changing the index to heap from the hastable using the pointer
        child = parent;
        parent = (child-1)/2;
    }
}

//Utility to Top Down Heapify the max heap
void TopDownHeapify(struct heap Heap[], int parent)
{
    int right_child = 2*parent + 2;
    int left_child = 2*parent + 1;

    while(right_child < length)
    {
        int max_child;
        if(Heap[left_child].count < Heap[right_child].count)
            max_child = right_child;
        else
            max_child = left_child;

        if(Heap[parent].count < Heap[max_child].count)
        {
            swap(Heap[parent],Heap[max_child]);
            Heap[max_child].point->indexH = max_child; //Changing the index to heap from the hastable using the pointer
            Heap[parent].point->indexH = parent; //Changing the index to heap from the hastable using the pointer
            parent = max_child;
            right_child = 2*parent + 2;
            left_child = 2*parent + 1;
        } 
        else
            break;
    }

    if(left_child<length && Heap[parent].count < Heap[left_child].count)
    {
        swap(Heap[parent],Heap[left_child]);
        Heap[left_child].point->indexH = left_child; //Changing the index to heap from the hastable using the pointer
        Heap[parent].point->indexH = parent; //Changing the index to heap from the hastable using the pointer
    }
}

//Utility to add a new node in the Heap
void HeapAdd(struct heap Heap[], struct hashtable** Table)
{
    Heap[length].count = 1;
    Heap[length].point = (*Table); //Pointer starts pointing at hashtable's node
    length++;
    BottomUpHeapify(Heap, length-1);
}

//Utility to hash the data
int Hash(int data)
{
    int hashvalue = data % PRIME;
    if (hashvalue == 0)
        hashvalue += PRIME;
    return hashvalue;    
}

//Utility to add an integer to the data structure
void Add(struct hashtable* Table[], struct heap Heap[], int data)
{
    int hashvalue = Hash(data);
    int flag = 1; //Flag to identify if the data is already present in the hashtable or not
    
    struct hashtable* temp = Table[hashvalue];
    while(Table[hashvalue] != NULL) 
    {
        //Finding if the data is already present or not
        if(Table[hashvalue]->data == data)
        {
            //Increasing count by 1 if the data is already present in the linked list
            Table[hashvalue]->count++;
            int count = Table[hashvalue]->count; 

            int index = Table[hashvalue]->indexH; //Index to the heap
            //Updating count in the heap
            Heap[index].count = count;
            BottomUpHeapify(Heap, index);

            flag = 0;
            break;
        }
        Table[hashvalue] = Table[hashvalue]->next;
    }
    Table[hashvalue] = temp;

    //If the data is not present already then
    if(flag == 1)
    {
        push(&Table[hashvalue], data); //Pushing it in the linked list
        HeapAdd(Heap, &Table[hashvalue]); //Adding it in the heap
    }

}

//Utility to delete elements with max frequency
void DeleteMaxFreq(struct hashtable* Table[], struct heap Heap[])
{
    int max = Heap[0].count;

    //If there are more than one element with the same maximum frequency delete all of them
    while(Heap[0].count == max) 
    {
        int hashvalue = Hash(Heap[0].point->data);

        deleteNode(&Table[hashvalue], Heap[0].point); //Deleting node from hashtable

        if(length == 1)
        {
            length--;
            break;
        }
        //Deleting from heap
        Heap[0] = Heap[--length];
        Heap[0].point->indexH = 0; //Changing the index to heap from the hastable using the pointer
        TopDownHeapify(Heap, 0);
    }
}


int main()
{
    struct hashtable* Table[MAX] = {NULL};
    struct heap Heap[MAX]; 

    printf("What would you like to do:\n");
    printf("1. Add an integer x\n");
    printf("2. Delete max frequency elements\n");
    printf("3. Print all elements\n");
    printf("4. Exit\n");

    while(1){
    
    int option;
    printf("Enter option number - ");
    scanf("%d",&option);

    if(option == 1)
    {
        int data;
        printf("Enter an integer x to add\n");
        scanf("%d",&data);
        Add(Table, Heap, data);
        printf("Done\n");
    }
    else if(option == 2)
    {
        if(length == 0)
            continue;
        DeleteMaxFreq(Table, Heap);
        printf("Done\n");
    }
    else if(option == 3)
    {
        for(int i = 1; i <= PRIME; i++)
        {
            struct hashtable* temp = Table[i];
            while(Table[i] != NULL)
            {
                printf("Data %d Count %d\n",Table[i]->data, Table[i]->count);
                Table[i] = Table[i]->next;
            }
            Table[i] = temp;
        }
    }
    else if(option == 4)
    {
        break;
    }
    else
    {
        printf("Enter valid option\n");
    }
    }

    return 0;
}