#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define PRIME 100003

//Binary Pattern Searching Rabin Karp with Hash Table

struct node{
    int data;
    struct node* link;
};

void append(struct node** head, int data)
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

int confirm(char* text, char* pattern[], struct node* table[], int y, int start_index)
{
    int len_pat = strlen(pattern[0]);
    int found = -1;
    int check = 0;
    struct node* temp = table[y];
    while(table[y] != NULL)
    {
        for(int j =0; j<len_pat; j++)
        {
            if(text[start_index+j]!=pattern[(table[y]->data)][j])
                break;
            else
                check++;
        }
        if(check==len_pat)
        {
            printf("Match Found - At %d index, pattern '%s' is found. \n",start_index,pattern[(table[y]->data)]);
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
    int len_pat = strlen(pattern[0]);
    int len_text = strlen(text);
    int match = -1;

    int y = (text[0]-'0');
    int pow = 2;

    for(int i = 1; i<len_pat; i++)
    {
        y = (2*y + (text[i]-'0'))%PRIME;
        pow *= 2;
    }

    if(table[y]!=NULL)
    {
        int found = confirm(text,pattern,table,y,0);
        if(found!=-1)
            match++;
    }


    for(int i =1; i<len_text-len_pat+1; i++)
    {
        y = (2*y + (text[i+len_pat-1]-'0') - (pow*(text[i-1]-'0')))%PRIME;

        if(y<0)
            y += PRIME;

        if(table[y]!=NULL)
        {
            int found = confirm(text,pattern,table,y,i);
            if(found!=-1)
                match++;
        }

    }

    if(match == -1)
        printf("No match found\n");

}

int main()
{
    struct node* table[1000000];

    char* text = "111011101111011101111011101111000111011101111011101111011101111";
    char* pattern[1000] = {"111011101111011101111011101111","011101111011101111011101111000"};

    for(int i=0; i<2; i++)
    {
        int N = (pattern[i][0]-'0');
        int len_pat = strlen(pattern[i]);

        for(int j = 1; j<len_pat; j++)
        {
            N = (2*N + (pattern[i][j]-'0'))%PRIME;
        }

        append(&table[N],i); 

    }

    stringMatch(text,pattern,table);

    return 0;
}