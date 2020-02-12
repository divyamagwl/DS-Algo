#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define swap(a, b) {char (temp); temp = a; a = b; b = temp;}

//lnum = larger length number --- snum = shorter length number
void addLarge(char* lnum, char* snum, char* sum)  //This function can add two very large numbers 
{
    char* add;
    add = (char*)malloc(100000*sizeof(char));

    int carry = 0;
    int llen = strlen(lnum); //llen = length of larger length number
    int slen = strlen(snum); //slen = length of shorter length number

    for(int i = 1; i<=slen; i++) //addition digit by digit till slen is exhausted 
    {
        int dig1 = lnum[llen-i] - '0'; // converts char to int
        int dig2 = snum[slen-i] - '0'; // converts char to int
        int sum_dig = dig1 + dig2 + carry; //sum of digits 
        add[i-1] = (sum_dig%10) + '0'; // storing remainder of sum of digits as char
        carry = sum_dig/10; //carry over for next digits
    }

    for(int i = slen+1; i<=llen ;i++) //addition digit by digit till llen is exhausted
    {
        int dig1 = lnum[llen-i] - '0';
        int sum_dig = dig1 + carry;
        add[i-1] = (sum_dig%10) + '0'; 
        carry = sum_dig/10;
    }

    if(carry!=0) //if carry is still left then storing it
        add[llen] = carry + '0';

    int flen = strlen(add); //final length of sum of numbers

    for(int i=1;i<=flen;i++) //Reversing the string and storing it in parameter sum pointer
        sum[i-1] = add[flen-i];
}

//lnum = larger length number --- snum = shorter length number
void multiplyLarge(char* lnum,char* snum,char* result) //This function can multiply two very large numbers
{
    char* singleDigitProduct;
    char* product;
    product = (char*)malloc(100000*sizeof(char));

    int llen = strlen(lnum); //llen = length of larger length number
    int slen = strlen(snum); //slen = length of shorter length number

    for(int i =1; i<=slen; i++)
    {
        singleDigitProduct = (char*)malloc(100000*sizeof(char));    
        int carry = 0;
        int dig2 = snum[slen-i] - '0'; // converts char to int

        for(int j= 1; j<=llen; j++)
        {
            int dig1 = lnum[llen-j] -'0'; // converts char to int
            int productDigits = (dig1*dig2) + carry; //product of single digits
            singleDigitProduct[j-1] = (productDigits%10) + '0'; //storing remainder of product of digits
            carry = productDigits/10; //carry over for the next digits
        }

        if(carry!=0) //if carry is still left then storing it
        {
            singleDigitProduct[llen] = carry + '0';
        }

        int len = strlen(singleDigitProduct);

        if (i == 1)
        {
            for(int k =1;k <= len ;k++) //Reversing string and storing it temporiraly in final product string variable
            {
                product[k-1] = singleDigitProduct[len-k];
            }
        }
        else
        {
            for(int k =0;k < len/2 ;k++) //Reversing the single digit product string
            {
                swap(singleDigitProduct[k],singleDigitProduct[len-k-1]);
            }
            for(int k =0;k<i-1;k++) //Adding additional 0s at the end of the string according to its value place
            {
                singleDigitProduct[len + k] = '0';
            }

            addLarge(singleDigitProduct,product,product); //Adding previously achieved product with the new single digit product 

        }
    }

    int flen = strlen(product);
    for(int i =0;i<flen;i++)
        result[i] = product[i];
}

int main()
{
	clock_t t; 
    t = clock();

    char* num1;
    char* num2;
    char* result;
    int diff;

    num1 = (char*)malloc(100000*sizeof(char));
    num2 = (char*)malloc(100000*sizeof(char));    
    result = (char*)malloc(100000*sizeof(char));    

    scanf("%s %s",num1,num2);

    diff = strlen(num1)-strlen(num2);

    if(diff>=0)
        multiplyLarge(num1,num2,result);
    else
        multiplyLarge(num2,num1,result);

    printf("%s",result);

	t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("\n\n%f ", time_taken);

    return 0;
}