#include<stdio.h>
#include<stdlib.h>
#define swap(x,y) {int (temp); temp = x; x = y; y = temp;}

void permutations(int array[], int left, int right)
{
	if(left == right)
	{
		for(int i = 0; i <= right; i++)
			printf("%d ",array[i]);
		printf("\n");
		return;
	}
	for(int i = left; i<= right; i++)
	{
		swap(array[left], array[i]);
		permutations(array, left+1, right);
		swap(array[left], array[i]);
	}
	return;
}

int main()
{
	int n;
	scanf("%d",&n);

	int* array = malloc(n*sizeof(int));
	for(int i = 1; i<= n; i++)
		array[i-1] = i;

	permutations(array, 0, n-1);

	return 0;
}
