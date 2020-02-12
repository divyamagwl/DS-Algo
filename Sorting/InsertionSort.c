#include<stdio.h>
#include<stdlib.h>
#define MAX 100000

void InsertionSort(int array[], int n)
{
    for(int i =1; i<n; i++)
    {
        int key = array[i];
        int j = i-1;
        while (j>=0 && array[j]>key)
        {
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = key;
    }
}

int main()
{
    int array[MAX];
    int n;
	scanf("%d",&n);
	for(int i =0; i<n; i++)
		scanf("%d",&array[i]);

    InsertionSort(array,n);
    for(int i =0; i<n; i++)
        printf("%d ",array[i]);
    printf("\n");
    return 0;
}