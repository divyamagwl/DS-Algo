#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define PRIME 100003

//Pattern Searching Rabin Karp with Hash Table

struct node{
    long long int data;
    struct node* link;
};

void append(struct node** head, long long int data)
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    struct node* last_node = (*head);
    new_node->data = data;
    new_node->link = NULL;
    if((*head) == NULL)
    {
        (*head) = new_node;
        return;
    }

    while (last_node->link != NULL)
    {
        last_node = last_node->link;
    }
    last_node->link = new_node;
}


long long int confirm(char* text, char* pattern[], struct node* table[], long long int y, long long int start_index)
{
    long long int len_pat = strlen(pattern[0]);
    long long int found = -1;
    long long int check = 0;
    struct node* temp = table[y];
    while(table[y] != NULL)
    {
        for(long long int j =0; j<len_pat; j++)
        {
            if(text[start_index+j]!=pattern[(table[y]->data)][j])
            {
                break;
            }
            else
            {
                check++;
            }
        }
        if(check==len_pat)
        {
            printf("Match Found - At %lld index, pattern '%s' is found. \n",start_index,pattern[(table[y]->data)]);
            found++;
        }
        check = 0;
        table[y] = table[y]->link;
    }
    table[y] = temp;

    return found;
}

void stringMatch(char* text, char* pattern[], struct node* table[])
{
    long long int len_pat = strlen(pattern[0]);
    long long int len_text = strlen(text);
    long long int match = -1;

    long long int y = (text[0]);
    long long int pow = 26%PRIME;

    for(long long int i = 1; i<len_pat; i++)
    {
        y = (26*y + (text[i]))%PRIME;
        pow *= 26%PRIME;
    }

    if(table[y]!=NULL)
    {
        long long int found = confirm(text,pattern,table,y,0);
        if(found!=-1)
            match++;
    }

    for(long long int i =1; i<len_text-len_pat+1; i++)
    {
        y = (26*y + (text[i+len_pat-1]) - (pow*(text[i-1])))%PRIME;

        if(y<0)
            y += PRIME;

        if(table[y]!=NULL)
        {
            long long int found = confirm(text,pattern,table,y,i);
            if(found!=-1)
                match++;
        }
    }

    if(match == -1)
        printf("No match found\n");

}

long long int main()
{
    struct node* table[1000000];

    char* text = "thisisastringwhichcanbeusedtofindmultiplesubstrings";
    char* pattern[1000] = {"thisisastri","hichcanbeus","gwhichcanbe","tofindmulti","thisisastrg"};

    for(long long int i=0; i<5; i++)
    {
        long long int N = (pattern[i][0]);
        long long int len_pat = strlen(pattern[i]);

        for(long long int j = 1; j<len_pat; j++)
        {
            N = (26*N + (pattern[i][j]))%PRIME;
        }

        append(&table[N],i); 
    }

    stringMatch(text,pattern,table);

    return 0;
}