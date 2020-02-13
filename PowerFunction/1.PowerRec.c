#include<stdio.h>

int recPow(int num, int power)
{
    if(power==0)
        return 1;
    else if(power%2 == 0)
        return recPow(num*num, power/2);
    else
        return num*recPow(num*num, power/2);
}

int main()
{
    int num, power;
    scanf("%d %d",&num,&power);
    printf("%d\n",recPow(num,power));
    return 0;
}