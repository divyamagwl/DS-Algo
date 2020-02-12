#include<stdlib.h>
#include<stdio.h>
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

int RFindRank(int numbers[], int left, int right, int rank)
{
    if(left<=right)
    {
        int pivot = (rand()%(right-left+1)) + left;
        swap(numbers[pivot],numbers[left]);
        int p_index = Partition(numbers, left+1, right, numbers[left]);

        if(rank == right-p_index+1)
            return numbers[p_index];
        else if(rank < right-p_index+1)
            RFindRank(numbers, p_index+1, right, rank);
        else
            RFindRank(numbers, left, p_index-1, rank-(right-p_index+1));
    }
    else
        return -1;
}

int main()
{
    int numbers[MAX];
    int n;
	scanf("%d",&n);
	for(int i =0; i<n; i++)
		scanf("%d",&numbers[i]);

    int r;
    scanf("%d",&r);

    int rank_number = RFindRank(numbers,0,n-1,r);

    printf("%d\n",rank_number);

    return 0;
}
