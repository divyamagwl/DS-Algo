#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define swap(a, b) {char (temp); temp = a; a = b; b = temp;}

int power(int x, int y) 
{ 
    int temp; 
    if( y == 0) 
        return 1; 
    temp = power(x, y/2); 
    if (y%2 == 0) 
        return temp*temp; 
    else
        return x*temp*temp; 
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
    int len = strlen(num);

    for(int i=0; i<len/2; i++) //Reversing the string
        swap( num[i], num[len-i-1]);

    for(int i = 0; i< 4-(len%4); i++)
        num[len+i] = '0';

    len = strlen(num);

    for(int i=0; i<len/2; i++) //Reversing the string
        swap( num[i], num[len-i-1]);
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
            int pow = power(10,j);
            sum[4*i + j] = (( (Isum[llen/4-i-1]+ carry) / pow) % 10) + '0';
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

    int flag =0;
    for(int i = 0; i<len2/4; i++)
    {
        for(int j =0; j<len1/4; j++)
        {
            Iproduct[flag] = Inum1[len1/4 - j -1]*Inum2[len2/4 - i -1]; 
            flag++;
        }
    }

    char* Cproduct; char* Ctemp; char* Cresult;

    Cproduct = (char*)malloc(100000*sizeof(char));
    Cresult = (char*)malloc(100000*sizeof(char));

    int foo = 0;
    int retain = 0;                                             

    for(int i =0; i<len1/4*len2/4; i++)
    {    
        flag = 0;
        Ctemp = (char*)malloc(100000*sizeof(char));
        int Ilen = numLen(Iproduct[i]);
        for(int j=0; j<Ilen; j++)
        {
            int pow = power(10,j);
            if(i==0)
            {
                Cproduct[flag] = (( Iproduct[i] / pow) % 10) + '0';
            }
            else
            {
                Ctemp[flag] = (( Iproduct[i] / pow) % 10) + '0';
            }
            flag++;
        }

        if(i==0)
        {
            int len2 = strlen(Cproduct);            
            for(int k =0;k < len2/2 ;k++) 
            {
                swap(Cproduct[k],Cproduct[len2-k-1]);
            }
            if(len1 == 4)
            {
                strcpy(Cresult,Cproduct);    
            }
        }
        
        if(i > 0)
        {
            int len = strlen(Ctemp);
            for(int k =0;k < len/2 ;k++) 
            {
                swap(Ctemp[k],Ctemp[len-k-1]);
            }

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

            int lentemp = strlen(Ctemp);
            int lenproduct = strlen(Cproduct);

            if (lentemp>lenproduct)
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

void factorialLarge(int num, char* factorial) //This function can find factorial of a very large number
{
    char* buffer;
    buffer = (char*)malloc(100000*sizeof(char));

    for(int i =0; i<=num; i++)
    {
        if(i==1 || i==0)
        {
            factorial[0] = '1';  
        }
        else
        {
            sprintf(buffer,"%d",i); //Converting integer into char value
            multiplyLarge(factorial,buffer,factorial);
        }
    }
}

int main()
{
	clock_t t; 
    t = clock();

    int num;
    char* factorial;
    factorial = (char*)malloc(100000*sizeof(char));

    scanf("%d",&num);
    factorialLarge(num,factorial);

    printf("%s\n",factorial);

	t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("\n\n%f ", time_taken);

    return 0;
}