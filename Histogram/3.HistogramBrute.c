// Q - Find rectangle of maximum area such that none of the end points are inside the rectangle

#include<stdio.h>
#include<stdlib.h>
#define MAX 100000

int LargestRectangle(int array[], int n)
{
    int max = 0;
    for(int i =0; i<n; i++)
    {
        for(int j= i+1; j<n; j++)
        {
            int min = array[i];
            for(int k = i+1; k<j+1; k++)
            {
                if(array[k]<min)
                    min = array[k];
            }
            if(min*(j-i) > max)
            {
                max = min*(j-i);
            }
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
