#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define swap(a, b) {char (temp); temp = a; a = b; b = temp;}

struct node{
    int data;
    struct node* link;
};

void push(struct node** head, int data)
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->link = (*head);
    (*head) = new_node;
}

void append(struct node** head, int data)
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    struct node* last_node = (*head);
    new_node->data = data;
    new_node->link = NULL;
    if((*head) == NULL)
    {
        (*head) = new_node;
        return;
    }

    while (last_node->link != NULL)
    {
        last_node = last_node->link;
    }
    last_node->link = new_node;
}

void printSum(struct node* SUM)
{
    if(SUM == NULL)
        return;

    printSum(SUM->link);
    printf("%d",SUM->data);
}

void store(char* num, struct node** Snum)
{
    for(int i =strlen(num)-1; i>=0; i--)
    {
        append(&(*Snum),(num[i]-'0'));
    }
}

int count(struct node* head)
{
    int count = 0;
    struct node* current = head;
    while(current!= NULL)
    {
        count++;
        current = current->link;
    }
    return count; 
}

void addLarge(struct node** Snum1,struct node** Snum2, struct node** Ssum)
{
    int carry = 0;
    int len1 = count(*Snum1);
    int len2 = count(*Snum2);

    for(int i=0; i<len1; i++)
    {
        int sum = 0;
        if(i<len2)
        {
            sum = (*Snum1)->data + (*Snum2)->data;
        }
        else
        {
            sum = (*Snum1)->data;
        }

        append(&(*Ssum),(sum + carry)%10);
        carry = (sum + carry)/10;

        (*Snum1) = (*Snum1)->link;
        if(i<len2)
        {
            (*Snum2) = (*Snum2)->link;
        }
    }

    if(carry!= 0)
    {
        append(&(*Ssum),carry);
    }
}

void multiplyLarge(struct node** Snum1, struct node** Snum2, struct node** product)
{
    int len1 = count(*Snum1);
    int len2 = count(*Snum2);
    for(int i=0; i<len2; i++)
    {
        int carry = 0;
        struct node* save1 = (*Snum1);
        struct node* save2 = (*Snum2);
        struct node* temp = NULL;
        for(int j =0; j<len1; j++)
        {
            int pro = 0;
            pro = ((*Snum1)->data)*((*Snum2)->data);

            if(i == 0)
            {
                append(&(*product),(pro+carry)%10);
            }
            else
            {
                append(&temp,(pro+carry)%10);
            }
            carry = (pro+carry)/10;
            (*Snum1) = (*Snum1)->link;
        }

        if(carry!=0)
        {
            if(i==0)
                append(&(*product),carry);
            else
                append(&temp,carry);
        }

        for(int k =0; k<i; k++)
        {   
            push(&temp,0);
        }

        if(i>0)
        {
            addLarge(&temp,&(*product),&(*product));
        }
        (*Snum1) = save1;
        (*Snum2) = save2->link;

    }
}

void factorialLarge(int num, struct node** factorial) //This function can find factorial of a very large number
{
    char* num1; char* num2;

    for(int i =0; i<=num; i++)
    {
        struct node* Snum1 = NULL;
        struct node* Snum2 = NULL;

        num1 = (char*)malloc(100000*sizeof(char));
        num2 = (char*)malloc(100000*sizeof(char));        
        
        if(i==1 || i==0)
        {
            sprintf(num1,"%d",1);
            store(num1, &(Snum1));
        }
        else
        {
            sprintf(num2,"%d",i);
            store(num2, &Snum2);

            multiplyLarge(&Snum2,&(*factorial),&(Snum1));
        }

        (*factorial) = Snum1;
    }
}

int main()
{
	clock_t t; 
    t = clock();

    int num;
    scanf("%d",&num);
    struct node* factorial = NULL; 

    factorialLarge(num,&factorial);

    printSum(factorial);
    printf("\n");

	t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("\n\n%f ", time_taken);

    return 0;
}