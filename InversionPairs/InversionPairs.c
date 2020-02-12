#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100000

int Merge(int array[], int left, int mid, int right)
{
    int l = left; int r = mid+1; int index = 0;
    int temp[1000];
    int pairs =0;
    while(l <= mid && r <= right)
    {
        if(array[l] <= array[r])
            temp[index++] = array[l++];
        else
        {
            temp[index++] = array[r++];
            pairs += mid-l+1;
        }
    }

    while (l<= mid) 
    {
        temp[index++] = array[l++];
    }
    while (r<= right)
    {
        temp[index++] = array[r++];
    }
    index = 0; l = left;
    while (l<=right)
    {
        array[l++] = temp[index++];
    }
    return pairs;
}

int MergeSort(int array[], int left, int right)
{
    if(left<right)
    {
        int mid = (left+right)/2;
        return MergeSort(array, left, mid)+ MergeSort(array, mid+1, right)+ Merge(array, left, mid, right);
    }
    return 0;
}

int main()
{
    int array[MAX];
    int n;
	scanf("%d",&n);
	for(int i =0; i<n; i++)
		scanf("%d",&array[i]);

    int pairs = MergeSort(array,0,n-1);
    for(int i =0; i<n; i++)
        printf("%d ",array[i]);
    printf("\nInversion pairs %d\n",pairs);
    return 0; 
}