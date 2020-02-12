#include<stdio.h>
#include<stdlib.h>
#define MAX 100000

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

void CountSort(int array[], int n, int sort[])
{
    int max = Max(array,n);
    int table[10000] = {0};
    for(int i =0; i<n; i++)
    {
        table[array[i]]++;
    }
    //Prefix Sum or Cumulative Sum
    for(int i= 1; i<=max; i++)
    {
        table[i] = table[i] + table[i-1];
    }

    for(int i = n-1; i>=0; i--)
    {
        sort[--table[array[i]]] = array[i];
    }
}

int main()
{
    int array[MAX];
    int n;
	scanf("%d",&n);
	for(int i =0; i<n; i++)
		scanf("%d",&array[i]);

    int sort[MAX];

    CountSort(array, n, sort);
    for(int i = 0; i<n; i++)
    {
        printf("%d ",sort[i]);
    }
    printf("\n");

    return 0;
}
