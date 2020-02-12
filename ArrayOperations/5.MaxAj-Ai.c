#include<stdio.h>
#define MAX 100000
//Max difference between elements such that j>i 
int maxDiff(int num[], int n)
{
    int i =0;
    int max = 0;
    for(int j =1; j<n; j++)
    {
        if(num[j]-num[i] > max)
            max =  num[j]-num[i];
        if(num[j]<num[i])
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

    printf("%d\n",maxDiff(num,n));

    return 0;
}