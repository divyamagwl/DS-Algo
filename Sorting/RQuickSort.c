#include<stdio.h>
#include<stdlib.h>
#define MAX 100000
#define swap(a, b) {int (temp); temp = a; a = b; b = temp;}

int Partition(int numbers[], int i, int j, int pivot)
{
    int left = i;
    int right = j;

    while(left <= right)
    {
        while(left <= right && numbers[left] <= pivot)
            left++;
        while(left <= right && numbers[right] > pivot)
            right--;
        if(left <= right)
        {
            swap(numbers[left], numbers[right]);
            left++;
            right--;
        }
    }

    int p_index = left-1;
    numbers[i-1] = numbers[p_index];
    numbers[p_index] = pivot; 
    return p_index;
}

void RQuickSort(int numbers[], int left, int right)
{
    if (left<right)
    {
        int pivot = (rand()%(right-left+1)) + left;
        swap(numbers[pivot],numbers[left]);
        int p_index = Partition(numbers, left+1, right, numbers[left]);
        RQuickSort(numbers, left, p_index-1);
        RQuickSort(numbers, p_index+1, right);
    }
}

int main()
{
    int numbers[MAX];
    int n;
	scanf("%d",&n);
	for(int i =0; i<n; i++)
		scanf("%d",&numbers[i]);

    RQuickSort(numbers, 0 , n-1);

    for(int i = 0; i<n; i++)
        printf("%d ",numbers[i]);
    printf("\n");

    return 0;
}