#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 1000000
#define swap(a, b) {char (temp); temp = a; a = b; b = temp;}

//lnum = larger length number --- snum = shorter length number
void addLarge(char* lnum, char* snum, char* sum)  //This function can add two very large numbers 
{
    char* add;
    add = (char*)malloc(MAX*sizeof(char));

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
    product = (char*)malloc(MAX*sizeof(char));

    int llen = strlen(lnum); //llen = length of larger length number
    int slen = strlen(snum); //slen = length of shorter length number

    for(int i =1; i<=slen; i++)
    {
        singleDigitProduct = (char*)malloc(MAX*sizeof(char));    
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


char* binPow(char* num, char* bin_power)
{
    char* result = (char*)malloc(MAX*sizeof(char));
    result = "1";
    int len = strlen(bin_power);
    while(len>0)
    {
        if(bin_power[len-1] == '1')
        {
            int diff = strlen(num)-strlen(result);        
            char* temp = (char*)malloc(MAX*sizeof(char));
            diff>=0 ? multiplyLarge(num,result,temp) : multiplyLarge(result,num,temp); 
            result = temp;
        }
        char* temp = (char*)malloc(MAX*sizeof(char));
        multiplyLarge(num,num,temp);
        num = temp;
        len--;
    }
    return result; 
}

char* divByTwo(char* string)
{
    char* number = (char*)malloc(MAX*sizeof(char));
    char* result = (char*)malloc(MAX*sizeof(char));
    int len = strlen(string);
    int carry;
    int next_carry = 0;
    for(int i = 0; i<len; i++)
    {
        carry = next_carry;
        if(string[i] == '1' || string[i] == '3' || string[i] == '5' || string[i] == '7' || string[i] == '9')
            next_carry = 5;
        else
            next_carry = 0;

        int num = ((string[i]-'0')/2) + carry;
        number[i] = num + '0';
    }

    int i = 0, k = 0;
    if(len!=1)
        while(number[i] == '0')
            i++;

    for(i; i<len; i++)
        result[k++] = number[i]; 

    return result;
}

char* decToBin(char* decimal)
{
    char* result = (char*)malloc(MAX*sizeof(char));
    char* number = (char*)malloc(MAX*sizeof(char));
    int remainder;
    int len = strlen(decimal);
    int i = 0;
    while(len != 1 || decimal[0] != '0')
    {
        remainder = (decimal[len-1]-'0')%2;
        number[i++] = remainder + '0';
        decimal = divByTwo(decimal);
        len = strlen(decimal);
    }

    for(int j =0; j<i; j++)
        result[j] = number[i-j-1];

    return result;
}

int main()
{
    char* num = malloc(10000);
    scanf("%s",num);
    char* power = malloc(10000);
    scanf("%s",power);
    char* result = binPow(num,decToBin(power));
    printf("%s\n",result);

    return 0;
}