#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define swap(a, b) {char (temp); temp = a; a = b; b = temp;}

//lnum = larger length number --- snum = shorter length number
void addLarge(char* lnum, char* snum, char* sum)  //This function can sum two very large numbers 
{
    int carry = 0;
    int llen = strlen(lnum); //llen = length of larger length number
    int slen = strlen(snum); //slen = length of shorter length number

    for(int i = 1; i<=slen; i++) //addition digit by digit till slen is exhausted 
    {
        int dig1 = lnum[llen-i] - '0'; // converts char to int
        int dig2 = snum[slen-i] - '0'; // converts char to int
        int sum_dig = dig1 + dig2 + carry; //sum of digits 
        sum[i-1] = (sum_dig%10) + '0'; // storing remainder of sum of digits as char
        carry = sum_dig/10; //carry over for next digits
    }

    for(int i = slen+1; i<=llen ;i++) //addition digit by digit till llen is exhausted
    {
        int dig1 = lnum[llen-i] - '0';
        int sum_dig = dig1 + carry;
        sum[i-1] = (sum_dig%10) + '0'; 
        carry = sum_dig/10;
    }

    if(carry!=0) //if carry is still left then storing it
        sum[llen] = carry + '0';

    int flen = strlen(sum); //final length of sum of numbers

    for(int i=0;i<flen/2;i++) //Reversing the string
        swap(sum[i],sum[flen-i-1]);
}

int main()
{
	clock_t t; 
    t = clock();

    char* num1; char* num2;
    char* sum;

    num1 = (char*)malloc(100000*sizeof(char));
    num2 = (char*)malloc(100000*sizeof(char));    
    sum = (char*)malloc(100000*sizeof(char));    

    scanf("%s %s",num1,num2);

    int diff = strlen(num1)-strlen(num2);

    if(diff>=0)
        addLarge(num1,num2,sum);
    else
        addLarge(num2,num1,sum);

    printf("%s",sum);

	t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("\n\n%f ", time_taken);

    return 0;
}
