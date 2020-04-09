// Q - Given a binary string (having alpha numeric values) of length 100,000 and an integer k, 
// implement an efficient algorithm to compute the length of the largest sub-string which repeats at least k times.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define PRIME 100003
#define MAX 100000

struct node{
    int count, index;
    struct node* next;
};

void push(struct node** head, int index)
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->index = index;
    new_node->count = 1;
    new_node->next = (*head);
    (*head) = new_node;
}

int Count(struct node* Table[], char* string, int k, int check_len, int hash_value,  int i)
{
    struct node* temp = Table[hash_value];
    int count = -1;
    int check = 0; 
    while(Table[hash_value] != NULL)
    {
        for(int j = 0; j<check_len; j++)
        {
            if(string[i+j] != string[j])
            {
                break;
            }
            else
                check++;
        }
        if(check == check_len)
        {
            Table[hash_value]->count++;
            count = Table[hash_value]->count;
            break;
        }
        check = 0;
        Table[hash_value] = Table[hash_value]->next;
    }
    Table[hash_value] = temp;
    return count;
}


bool check(struct node* Table[], char* string, int check_len, int k)
{
    int hash_value = (string[0]-'0');
    int pow = 2;	
    int str_len = strlen(string);
    
    for(int i = 1; i<check_len; i++)
    {
        hash_value = (2*hash_value + (string[i]-'0'))%PRIME;
        pow *= 2;
    }
    push(&Table[hash_value], 0);

    for(int i = 1; i< str_len-check_len+1; i++)
    {
        hash_value = (2*hash_value + (string[i+check_len-1]-'0') - (pow*(string[i-1]-'0'))) % PRIME;
        
        if (hash_value < 0)
            hash_value += PRIME;

        if(Table[hash_value] == NULL)
            push(&Table[hash_value], i);
        else
        {
            if(Count(Table, string, k, check_len, hash_value, i) == k)
                return true;
        }                
    }

    return false;
}


int lengthBS(char* string, int k, int left, int right)
{
    struct node* Table[2*MAX] = {NULL};
    int mid = (left+right)/2;

    if(left < right)
    {
        if(check(Table, string, mid, k))
            return lengthBS(string, k, mid+1, right);
        else
            return lengthBS(string, k, left, mid-1);
    }
    else
    {
        if(check(Table, string, mid, k))
            return mid;
        else
            return mid-1;
    } 

}

int main()
{
    char* string;
    string =(char*)calloc(MAX, sizeof(char));
    printf("Enter the string-\n");
    scanf("%s",string);

    int length = strlen(string);
    int k;
    printf("Enter k-\n");
    scanf("%d",&k);
    
    int max_len = lengthBS(string, k, 0, length-1);
    printf("Maximum length which repeats atleast k times is %d\n",max_len);

    return 0;
}
