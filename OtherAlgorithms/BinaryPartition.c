#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Q- We have to find the index where the number of 0s on the left (including the partition) = no. of 1s on right

int binaryPartition(char* string)
{
    int left = 0;
    int right = strlen(string)-1;
    int zeroes = 0;
    int ones = 0;
    int partition_index = -1;

    while ((left<=right || zeroes!=ones))
    {
        if(zeroes <= ones)
        {
            if(string[left]=='0')
            {
                zeroes++;
            }
            left++;
        }
        else
        {
            if(string[right]=='1')
            {
                ones++;
            }
            right--;
        }
    }

    if((left-1)>right)
    {
        partition_index = left-2;
    }
    else
    {
        partition_index = right;
    }

    return partition_index;
}

int main()
{
    char* string = "00101110011001";

    int result = binaryPartition(string);
    if (result<0)
        printf("There does not exist any index for the condition to be true\n");
    else
        printf("Required index is %d\n",result);

    return 0;
}