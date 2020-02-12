#include<stdio.h>
#define MAX 100000

int maxDiff(int num[], int n)
{
    int max = -1000000;
    int min = 1000000;
    for(int i =0; i<n; i++)
    {
        if(num[i]>max)
            max = num[i];
        if(num[i]<min)
            min = num[i];
    }
    return max-min;
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