#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Binary Pattern Searching Rabin Karp without hashing

int main()
{
    char* text = "10111010111011001110101110110011110101110110011101111010111011101011101100111010111011001111010111011";
    char* pattern = "11101011101100111010111011001111";

    int len_pat = strlen(pattern);
    int len_text = strlen(text);

    
    int N = (pattern[0]-'0');
    int y = (text[0]-'0');
    int pow = 2;
    int match = -1;

    for(int i = 1; i<len_pat; i++)
    {
        N = 2*N + (pattern[i]-'0');
        y = 2*y + (text[i]-'0');
        pow *= 2;
    }

    if(N==y)
    {
        printf("Pattern match found at 0 index\n");
        match++;
    }

    for(int i =1; i<len_text-len_pat+1; i++)
    {
        y = 2*y + (text[i+len_pat-1]-'0') - (pow*(text[i-1]-'0'));
        
        if(y == N)
        {
            printf("Pattern match found at %d index\n",i);
            match++;
        }
    }

    if(match == -1)
        printf("No match found\n");

    return 0;
}