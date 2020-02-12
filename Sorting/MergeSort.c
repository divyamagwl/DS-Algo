#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100000

void Merge(int array[], int left, int mid, int right)
{
    int l = left; int r = mid+1; int index = 0;
    int temp[1000];
    while(l <= mid && r <= right)
    {
        if(array[l] <= array[r])
            temp[index++] = array[l++];
        else
            temp[index++] = array[r++];
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

}

void MergeSort(int array[], int left, int right)
{
    if(left<right)
    {
        int mid = (left+right)/2;
        MergeSort(array, left, mid);
        MergeSort(array, mid+1, right);
        Merge(array, left, mid, right);
    }
}

int main()
{
    int array[MAX];
    int n;
	scanf("%d",&n);
	for(int i =0; i<n; i++)
		scanf("%d",&array[i]);

    MergeSort(array,0,n-1);
    for(int i =0; i<n; i++)
        printf("%d ",array[i]);
    printf("\n");
    return 0; 
}