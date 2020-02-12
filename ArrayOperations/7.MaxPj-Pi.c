#include<stdio.h>
#define MAX 100000

void cumulativeSum(int num[], int n, int prefixSum[])
{
    prefixSum[0] = 0;
    for(int i =1; i<n+1; i++)
    {
        prefixSum[i] = prefixSum[i-1] + num[i-1]; 
    }
}

int maxDiffcum(int prefixSum[], int n)
{
    int i =0;
    int max = -100000;
    for(int j =1; j<n+1; j++)
    {
        if(prefixSum[j]-prefixSum[i] > max)
            max = prefixSum[j]-prefixSum[i];
        if(prefixSum[j]<prefixSum[i])
            i = j;
    }
    return max;
}

int main()
{
    int num[MAX];
    int n;
	scanf("%d",&n);
	for(int i =0; i<n; i++)
		scanf("%d",&num[i]);

    int prefixSum[MAX];
    cumulativeSum(num,n,prefixSum);

    printf("%d\n",maxDiffcum(prefixSum, n));

    return 0;
}