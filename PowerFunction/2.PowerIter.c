#include<stdio.h>

int loopPow(int num, int power)
{
    int result = 1;
    while(power>0)
    {
        if(power%2==1)
            result = result*num;
        num = num*num;
        power = power/2;
    }
    return result; 
}

int main()
{
    int num, power;
    scanf("%d %d",&num,&power);
    printf("%d\n",loopPow(num,power));
    return 0;
}