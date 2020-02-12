#include<stdlib.h>
#include<stdio.h>
#include<string.h>

//Binary Pattern Searching Rabin Karp with hashing

int main()
{
    char* text = "000111010111011001110101110110011110101110110011101111010111011101011101100111010111011001111010111011";
    char* pattern = "1110101110110011101011101100111";

    int len_pat = strlen(pattern);
    int len_text = strlen(text);

    int prime = 1000003;
    int check = 0;
    int N = (pattern[0]-'0');
    int y = (text[0]-'0');
    int pow = 2;
    int match = -1;

    for(int i = 1; i<len_pat; i++)
    {
        N = (2*N + (pattern[i]-'0'))%prime;
        y = (2*y + (text[i]-'0'))%prime;
        pow *= 2;
    }

    if(N == y)
    {
        for(int j =0; j<len_pat; j++)
        {
            if(text[j]!=pattern[j])
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
            printf("Pattern match found at %d index\n",0);
            match++;
        }
        check = 0;
    }

    for(int i =1; i<len_text-len_pat+1; i++)
    {
        y = (2*y + (text[i+len_pat-1]-'0') - (pow*(text[i-1]-'0')))%prime;

        if(y<0)
            y += prime;

        if(N == y)
        {
            for(int j =0; j<len_pat; j++)
            {
                if(text[i+j]!=pattern[j])
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
                printf("Pattern match found at %d index\n",i);
                match++;
            }
            check = 0;
        }
    }

    if(match == -1)
        printf("No match found\n");

    return 0;
}