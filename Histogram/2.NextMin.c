// Q- Create an array which has the indices of the first number smaller than the current number
// E.g. A = {6,13,7,8,4,9}
//    ans = {4,2,4,4,-1,-1}

#include<stdio.h>
#include<stdlib.h>
#define MAX 100000

void NextMin(int array[], int n, int result[])
{
    int* stack = malloc(n*sizeof(int));
    int top = -1; 
    for(int i =0; i<n; i++)
    {
        if(top < 0)
        {
            top++;
            stack[top] = i;
        }
        else
        {
            if(array[stack[top]] < array[i])
            {
                top++;
                stack[top] = i;
            }
            else
            {
                while (top >= 0 && array[stack[top]] >= array[i])
                {
                    result[stack[top]] = i;
                    top--;
                }
                top++;
                stack[top] = i;
            }
        }
    }
    while (top >= 0)   
    {
        result[stack[top--]] = -1;
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    
    int* array = malloc(n*sizeof(int));    
    for(int i =0; i<n; i++)
        scanf("%d",&array[i]);
    
    int* result = malloc(n*sizeof(int));
    
    NextMin(array,n,result);
    
    for(int i =0; i<n; i++)
    {
        printf("%d ",result[i]); 
    }
    printf("\n");

    return 0;
}