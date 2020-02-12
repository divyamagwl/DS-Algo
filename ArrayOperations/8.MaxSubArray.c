#include<stdio.h>
#define MAX 1000000

int maxDiffcum(int num[], int n)
{
    int max = -1000000;
    int sum = 0;
    int i = 0;
    int i_max =0;
    int j_max = 0;
    for(int j= 0; j<n ; j++)
    {
        sum += num[j];
        if(sum>max)
        {
            max = sum;
            i_max = i+1;
            j_max = j;
        }
        if(sum<0)
        {
            sum =0;
            i = j;
        }
    }
    printf("imax = %d jmax = %d\n",i_max,j_max);
    return max;
}

int main()
{
    int num[MAX];
    int n;
	scanf("%d",&n);
	for(int i =0; i<n; i++)
		scanf("%d",&num[i]);

    printf("%d\n",maxDiffcum(num, n));

    return 0;
}