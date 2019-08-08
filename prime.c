#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int isprime(int n)
{       if(n==1)
         return 0;
        else if(n==2)   
        return 1;
        else if(n%2==0)
         return 0;              
        else
        {
                for(int i=3;i<n/2;i+=2)
                {       if(n%i==0)
                                return 0;
                }
        return 1;
        }
}

void result(int *arr,int n)
{	int c=1;
	for(int i=0;i<n;i++)
	{	if(isprime(arr[i])==1)
		{	if(c%2!=0)
			{	printf("%d ",arr[i]);
				c++;
			}
			else
			{	c++;
				continue;
			}
		}
		else
			continue;
	}	
}
void main()
{       int *arr;
	int n;
        arr=(int *)malloc(50);
	printf("Enter the array size:");
	scanf("%d",&n);
        printf("Enter the array element:");
        for(int i=0;i<n;i++)
        {       printf("%d->",i+1);
                scanf("%d",&arr[i]);
        }
	result(arr,n);
}
