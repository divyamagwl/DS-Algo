#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

//Binary Pattern Searching Bruteforce method

int btod(char* binary)
{
    int num = 0;
    int len = strlen(binary);
    for(int i =0; i<len; i++)
    {
        num += (binary[len-i-1]-'0')*(pow(2,i)); 
    }
    return num;
}

int main()
{
    char* text = "010101110101101010110100101";
    char* pattern = "0101";

    int num = btod(pattern);
    int match;

    for(int i =0; i<strlen(text); i++)
    {
        char* check = (char*)malloc(1000*sizeof(char));
        int flag = -1;
        for(int j =0; j<strlen(pattern); j++)
        {
            check[j] = text[i+j];
        }
        int checknum = btod(check);

        if(checknum == num)
        {
            printf("Pattern match found at %d index\n",i);
            match++;
        }
    }

    if(match==0)
        printf("No match found\n");

    return 0;
}
