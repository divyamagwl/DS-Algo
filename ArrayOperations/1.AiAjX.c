#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define swap(a, b) {int (temp); temp = a; a = b; b = temp;}
#define MAX 100000

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

bool fixedSum(int num[], int sum, int left, int right)
{
    RQuickSort(num,left,right);
    
    while(left <= right)
    {
        if(num[left]+num[right] == sum)
            return true;
        else if(num[left] + num[right] < sum)
            left++;
        else
            right--;
    }
    return false;
} 

int main()
{
    int num[MAX];
    int n;
	scanf("%d",&n);
	for(int i =0; i<n; i++)
		scanf("%d",&num[i]);

    int sum;
    scanf("%d",&sum);

    if(fixedSum(num,sum,0,n-1))
        printf("Yes the sum exists in the array\n");
    else
        printf("No the sum does not exist\n");

    return 0;
}