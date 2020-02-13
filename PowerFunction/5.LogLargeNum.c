#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100000

char* divByTwo(char* string)
{
    char* number = (char*)malloc(MAX*sizeof(char));
    char* result = (char*)malloc(MAX*sizeof(char));
    int len = strlen(string);
    int carry;
    int next_carry = 0;
    for(int i = 0; i<len; i++)
    {
        carry = next_carry;
        if(string[i] == '1' || string[i] == '3' || string[i] == '5' || string[i] == '7' || string[i] == '9')
            next_carry = 5;
        else
            next_carry = 0;

        int num = ((string[i]-'0')/2) + carry;
        number[i] = num + '0';
    }

    int i = 0, k = 0;
    if(len!=1)
        while(number[i] == '0')
            i++;

    for(i; i<len; i++)
        result[k++] = number[i]; 

    return result;
}

char* decToBin(char* decimal)
{
    char* result = (char*)malloc(MAX*sizeof(char));
    char* number = (char*)malloc(MAX*sizeof(char));
    int remainder;
    int len = strlen(decimal);
    int i = 0;
    while(len != 1 || decimal[0] != '0')
    {
        remainder = (decimal[len-1]-'0')%2;
        number[i++] = remainder + '0';
        decimal = divByTwo(decimal);
        len = strlen(decimal);
    }

    for(int j =0; j<i; j++)
        result[j] = number[i-j-1];

    return result;
}

int main()
{
    char* num = malloc(MAX);
    scanf("%s",num);
    int log = strlen(decToBin(num)) -1;
    printf("%d\n",log);

    return 0;
}