// We have an array arr[0 . . . n-1]. We should be able to
// 1 Find the minimum of elements from index l to r where 0 <= l <= r <= n-1
// 2 Change value of a specified element of the array to a new value x. We need to do arr[i] = x where 0 <= i <= n-1.
// Time Complexity = O(logn) for both queries

#include<stdio.h>
#include<stdlib.h>
#define MAX 100000
#define INT_MAX 2147483646

void BuildSegmentTree(int array[], int segment_tree[], int n)
{
    for(int i = 0; i<n; i++)
    {
        segment_tree[n-1+i] = i;
    }
    for(int i = n-2; i > -1; i--)
    {
        if(array[segment_tree[2*i+1]] > array[segment_tree[2*i+2]])
        {
            segment_tree[i] = segment_tree[2*i+2];
        }
        else
        {
            segment_tree[i] = segment_tree[2*i+1];
        }
    }
}

void UpdateSegmentTree(int array[], int segment_tree[], int n, int index, int value)
{
    array[index] = value;
    int parent = ((n-1+index)-1)/2;

    while( parent > 0)
    {
        if(array[segment_tree[2*parent+1]] > array[segment_tree[2*parent+2]])
        {
            segment_tree[parent] = segment_tree[2*parent+2];
        }
        else{
            segment_tree[parent] = segment_tree[2*parent+1];
        }
        parent = (parent-1)/2;
    }

    segment_tree[0] = array[segment_tree[1]] > array[segment_tree[2]] ? segment_tree[2] : segment_tree[1];
}

int ReturnMinQuery(int array[], int segment_tree[], int n, int i, int j, int start, int end, int root)
{    
    if (start > j || end < i)
    {
        return n;
    }
    else if (start >= i && end <= j)
    {
        return segment_tree[root];
    }

    int mid = (start+end)/2;

    int left = ReturnMinQuery(array,segment_tree,n,i,j,start,mid,2*root+1);
    int right = ReturnMinQuery(array,segment_tree,n,i,j,mid+1,end,2*root+2);

    if(array[left] < array[right])
        return left;
    else
        return right;
}

void PrintSegmentTree(int segment_tree[], int n)
{
    for(int i= 0; i<2*n-1 ; i++)
    {
        printf("%d ",segment_tree[i]);
    }
    printf("\n");
}

int main()
{
    int n; int array[MAX];
    int segment_tree[MAX];

    scanf("%d",&n);

    for(int i= 0; i<n ; i++)
    {
        scanf("%d",&array[i]);
    }

    array[n] = INT_MAX;

    BuildSegmentTree(array,segment_tree,n);
    printf("Built Segment Tree - ");
    PrintSegmentTree(segment_tree,n);

    UpdateSegmentTree(array,segment_tree,n,6,14); //Update element according to given query 
    printf("Updated Segment Tree - ");
    PrintSegmentTree(segment_tree,n);

    int index = ReturnMinQuery(array,segment_tree,n,2,6,0,n-1,0); //Update range according to given query
    printf("Minimum value in given range (2,6) is %d\n",array[index]);

    return 0;
}