#include<stdio.h>
#include<string.h>

//Power of a number if the power is given in binary string form

int binPow(int num, char* bin_power)
{
    int result = 1;
    int len = strlen(bin_power);
    while(len>0)
    {
        if(bin_power[len-1] == '1')
            result = result*num;
        num = num*num;
        len--;
    }
    return result; 
}

int main()
{
    int num;
    scanf("%d",&num);
    char* binary = malloc(10000);
    scanf("%s",binary);
    printf("%d\n",binPow(num,binary));
    return 0;
}