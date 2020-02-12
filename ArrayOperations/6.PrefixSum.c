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

int main()
{
    int num[MAX];
    int n;
	scanf("%d",&n);
	for(int i =0; i<n; i++)
		scanf("%d",&num[i]);

    int prefixSum[MAX];
    cumulativeSum(num,n,prefixSum);
    for(int i =0; i<=n; i++)
    {
        printf("%d ",prefixSum[i]);
    }
    printf("\n");
    return 0;
}