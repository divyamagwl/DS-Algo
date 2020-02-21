// Q - Find rectangle of maximum area such that none of the end points are inside the rectangle

#include<stdio.h>
#include<stdlib.h>
#define MAX 100000

void RightMinArray(int array[], int n, int result[])
{
    int* stack = malloc(n*sizeof(int));
    int top = -1; 
    for(int i =0; i<n; i++)
    {
        if(top < 0)
            stack[++top] = i;
        else
        {
            if(array[stack[top]] < array[i])
                stack[++top] = i;
            else
            {
                while (top >= 0 && array[stack[top]] >= array[i])
                {
                    result[stack[top]] = i;
                    top--;
                }
                stack[++top] = i;
            }
        }
    }
    while (top >= 0)   
    {
        result[stack[top--]] = n;
    }
}

void LeftMinArray(int array[], int n, int result[])
{
    int* stack = malloc(n*sizeof(int));
    int top = -1; 
    for(int i = n-1; i>=0; i--)
    {
        if(top < 0)
            stack[++top] = i;
        else
        {
            if(array[stack[top]] < array[i])
                stack[++top] = i;
            else
            {
                while (top >= 0 && array[stack[top]] >= array[i])
                {
                    result[stack[top]] = i;
                    top--;
                }
                stack[++top] = i;
            }
        }
    }
    while (top >= 0)   
    {
        result[stack[top--]] = -1;
    }
}

int LargestRectangle(int array[], int n)
{
    int* right_min = malloc(n*sizeof(int));
    int* left_min = malloc(n*sizeof(int));
    RightMinArray(array,n,right_min);
    LeftMinArray(array,n,left_min);

    int max = 0;
    for(int i =0; i<n; i++)
    {
        if(max < (right_min[i]-2-left_min[i]) * array[i] )
        {
            max = (right_min[i]-2-left_min[i]) * array[i];
        }
    }

    return max;
}

int main()
{
    int n;
	scanf("%d",&n);

    int* array = malloc(n*sizeof(int));    
    for(int i =0; i<n; i++)
        scanf("%d",&array[i]);

    int max_area = LargestRectangle(array,n);
    printf("%d\n",max_area);
    return 0;
}
