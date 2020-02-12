#include<stdio.h>
#include<stdlib.h>
#define MAX 100000

int Length(int n)
{
    int len =0;
    if(n==0)
        return 1;
    while(n!=0)
    {
        len++;
        n = n/10;
    }
    return len;
}

int Max(int array[], int n)
{
    int max = 0;
    for(int i =0; i<n; i++)
    {
        if(array[i]>max)
            max = array[i];
    }
    return max;
}

int RadixSort(int array[], int n)
{
    int max = Max(array,n);
    int length = Length(max);
    int place = 1;

    while(length--)
    {
        int table[10] = {0};
        int temp[1000];
        for(int i =0; i<n; i++)
        {
            int digit = (array[i]/place)%10;
            table[digit]++;
        }
        //Prefix Sum or Cumulative Sum
        for(int i= 1; i<10; i++)
        {
            table[i] = table[i] + table[i-1];
        }

        for(int i = n-1; i>=0; i--)
        {
            int digit = (array[i]/place)%10;
            temp[--table[digit]] = array[i];
        }

        for(int i= 0; i<n; i++)
        {
            array[i] = temp[i];
        }
        place = place*10;
    }
}

int main()
{
    int array[MAX];
    int n;
	scanf("%d",&n);
	for(int i =0; i<n; i++)
		scanf("%d",&array[i]);

    RadixSort(array, n);
    for(int i = 0; i<n; i++)
    {
        printf("%d ",array[i]);
    }
    printf("\n");

    return 0;
}