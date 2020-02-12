#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#define PRIME 10003

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

void hashTable(char* string, int length, struct node* table[])
{
    int N = (string[0]-'0');
    int pow = 2%PRIME;

    for(int i = 1; i<length; i++)
    {
        N = (2*N + (string[i]-'0'))%PRIME;
        pow *= 2%PRIME;
    }
    push(&table[N], 0);

    for(int i = 1; i<strlen(string)-length+1; i++)
    {     
        N = (2*N + (string[i+length-1]-'0') - (pow*(string[i-1]-'0')))%PRIME;
        if(N<0)
            N += PRIME;
        push(&table[N], i);
    }
}

bool confirm(char* text, char* pattern, int length, struct node* table[], int y, int start_index)
{
    int check = 0;
    struct node* temp = table[y];
    while(table[y] != NULL)
    {
        for(int j =0; j<length; j++)
        {
            if(text[start_index+j]!=pattern[(table[y]->data) + j])
                break;
            else
                check++;
        }
        
        if(check==length)
        {
            table[y] = temp;
            return true;
        }
        check = 0;
        table[y] = table[y]->link;
    }
    table[y] = temp;

    return false;
}

bool subString(char* T1, char* T2, int length, struct node* table[])
{
    int y = (T1[0]-'0');
    int pow = 2%PRIME;

    for(int i = 1; i<length; i++)
    {
        y = (2*y + (T1[i]-'0'))%PRIME;
        pow *= 2%PRIME;
    }
    if(y<0)
        y += PRIME;

    if(table[y] != NULL)
    {
        if(confirm(T1,T2,length,table,y,0))
            return true;
    }

    for(int i = 1; i<strlen(T1)-length+1; i++)
    {     
        y = (2*y + (T1[i+length-1]-'0') - (pow*(T1[i-1]-'0')))%PRIME;
        if(y<0)
            y += PRIME;

        if(table[y]!=NULL)
        {
            if(confirm(T1,T2,length,table,y,i))
                return true;
        }
    }
    return false;
}

int lengthBS(char* T1, char* T2, int l, int r)
{
    int mid = (l+r)/2;
    struct node* table[100000] = {NULL};
    hashTable(T2,mid,table);

    if(l == r)
    {
        if(subString(T1, T2, mid, table))
            return mid;
        else
            return mid-1;
    }
    if(l<r)
    {
        if(subString(T1, T2, mid, table))
        {
            return lengthBS(T1, T2, mid+1, r);
        }
        else
        {
            return lengthBS(T1, T2, l, mid-1);
        }
    }
    return 0;
}

int main()
{
    char* T1 = {"1010101101010110110101010101000000000000000000"};
    char* T2 = {"11111111110101011011010101010100000000"};

    int LCS = lengthBS(T1,T2,1,strlen(T2));
    printf("Length of longest common pattern is %d\n",LCS);

    return 0;
}