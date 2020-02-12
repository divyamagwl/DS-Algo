#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define swap(a, b) {char (temp); temp = a; a = b; b = temp;}

void reverse(char* string)
{
    int length = strlen(string); 
    for(int i =0; i < length/2 ; i++) 
    {
        swap(string[i],string[length-i-1]);
    }
}

int numLen(int num)
{
    int length = 0;
    while (num>0)
    {
        length++;
        num = num/10;
    }
    return length;
}

void addZeroes(char* num)
{
    reverse(num);

    int len = strlen(num);
    for(int i = 0; i< 4-(len%4); i++)
        num[len+i] = '0';

    reverse(num);
}

void addLarge(char* lnum,char* snum, char* result)
{
    char* sum;
    sum = (char*)malloc(100000*sizeof(char));    

    if (strlen(lnum)%4 != 0)
        addZeroes(lnum);

    if (strlen(snum)%4 != 0)
        addZeroes(snum);

    int llen = strlen(lnum);
    int slen = strlen(snum);
    int diff = llen - slen;

    int* Ilnum; int* Isnum;
    int* Isum;

    Ilnum = (int*)malloc(100000*sizeof(int));
    Isnum = (int*)malloc(100000*sizeof(int));    
    Isum = (int*)malloc(100000*sizeof(int));    

    for(int i=0; i<llen; i+= 4)
    {
        Ilnum[i/4] = 1000*(lnum[i] - '0') + 100*(lnum[i+1] - '0') + 10*(lnum[i+2] - '0') + 1*(lnum[i+3] - '0');

        if(i<slen)
            Isnum[i/4] = 1000*(snum[i] - '0') + 100*(snum[i+1] - '0') + 10*(snum[i+2] - '0') + 1*(snum[i+3] - '0');
    }

    for(int i=0; i<llen/4; i++)
    {
        if(i<diff/4)
            Isum[i] = Ilnum[i];
        else
            Isum[i] = Ilnum[i] + Isnum[i-(diff/4)];
    }

    int carry = 0;
    for(int i=0; i<llen/4; i+=1)
    {
        for(int j=0; j<4; j++)
        {
            int power = pow(10,j);
            sum[4*i + j] = (( (Isum[llen/4-i-1]+ carry) / power) % 10) + '0';
        }
        carry = (Isum[llen/4-i-1]+ carry) /10000;
    }

    if (carry!= 0)
        sum[llen] = carry + '0';

    int flen = strlen(sum); //final length of sum of numbers

    for(int i =flen-1; i>=0; i--)
        if(sum[i] == '0')
            sum[i] = '\0';
        else
            break;

    flen = strlen(sum);

    for(int i=0; i<flen; i++) //Reversing the string and storing it in parameter result pointer
    {
        result[i] = sum[flen-i-1];
    }
}

void multiplyLarge(char* num1, char*num2, char*result)
{
    if (strlen(num1)%4 != 0)
        addZeroes(num1);

    if (strlen(num2)%4 != 0)
        addZeroes(num2);

    int* Inum1; int* Inum2;
    int* Iproduct;

    Inum1 = (int*)malloc(100000*sizeof(int));
    Inum2 = (int*)malloc(100000*sizeof(int));    
    Iproduct = (int*)malloc(100000*sizeof(int));

    int len1 = strlen(num1);    
    int len2 = strlen(num2);

    for(int i=0; i<len1; i+=4)
    {
        Inum1[i/4] = 1000*(num1[i] - '0') + 100*(num1[i+1] - '0') + 10*(num1[i+2] - '0') + 1*(num1[i+3] - '0');

        if(i<len2)
            Inum2[i/4] = 1000*(num2[i] - '0') + 100*(num2[i+1] - '0') + 10*(num2[i+2] - '0') + 1*(num2[i+3] - '0');
    }

    int index =0;
    for(int i = 0; i<len2/4; i++)
    {
        for(int j =0; j<len1/4; j++)
        {
            Iproduct[index] = Inum1[len1/4 - j -1]*Inum2[len2/4 - i -1]; 
            index++;
        }
    }

    char* Cproduct; char* Ctemp; char* Cresult;

    Cproduct = (char*)malloc(100000*sizeof(char));
    Cresult = (char*)malloc(100000*sizeof(char));

    int foo = 0;
    int retain = 0;                                             

    for(int i =0; i<len1/4*len2/4; i++)
    {    
        int flag = 0;
        Ctemp = (char*)malloc(100000*sizeof(char));
        int Ilen = numLen(Iproduct[i]);
        for(int j=0; j<Ilen; j++)
        {
            int power = pow(10,j);
            if(i==0)
            {
                Cproduct[flag] = (( Iproduct[i] / power) % 10) + '0';
            }
            else
            {
                Ctemp[flag] = (( Iproduct[i] / power) % 10) + '0';
            }
            flag++;
        }

        if(i==0)
        {
            reverse(Cproduct);
            if(len1 == 4)
            {
                strcpy(result,Cproduct);
                return;    
            }
        }        
        else
        {
            reverse(Ctemp);

            if((i%(len1/4))==0)
            {   
                foo++;
                retain = foo;
            }
            else
            {
                retain++;
            }

            for(int k =flag; k< flag+4*retain;k++ )
            {
                Ctemp[k] = '0';
            }

            if (strlen(Ctemp)>strlen(Cproduct))
            {
                addLarge(Ctemp,Cproduct,Cresult);
            }
            else
            {
                addLarge(Cproduct,Ctemp,Cresult);
            }
            strcpy(Cproduct,Cresult);
        }
    }
    strcpy(result,Cresult);
}


int main()
{
	clock_t t; 
    t = clock();

    char* num1; char* num2;
    char* result;

    num1 = (char*)malloc(100000*sizeof(char));
    num2 = (char*)malloc(100000*sizeof(char));    
    result = (char*)malloc(100000*sizeof(char));

    scanf("%s %s",num1,num2);

    int diff = strlen(num1)-strlen(num2);

    if(diff>=0)
        multiplyLarge(num1,num2,result);
    else
        multiplyLarge(num2,num1,result);

    printf("%s\n",result);

	t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("\n\n%f ", time_taken);

    return 0;
}