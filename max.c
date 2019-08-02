#include<stdio.h>
#include<stdlib.h>

int * rem(int *arr,int max)
{	int *ar;
	int j=0;
	ar=(int *)malloc(10);
	for(int i=0;i<5;i++)
	{	if(arr[i]!=max)
		ar[j++]=arr[i];
		else
		continue;
	}
	return ar;

}
int max(int *arr)
{	int max=arr[0];
	 
	for(int i=0;i<5;i++)
	{	if(max<arr[i])
		max=arr[i];
		else
		max=max;
	}
	return max;
	
}
void main()
{	int *arr;
	int *ar;
	ar=(int *)malloc(10);
	arr=(int *)malloc(10);	
	printf("Enter the array element:");
	for(int i=0;i<5;i++)
	{	printf("\n%d->",i+1);
		scanf("%d",&arr[i]);
	}
	int m1=max(arr);
 	arr=rem(arr,m1);
	int m2=max(arr);

	ar=arr;
	arr=rem(ar,m2);
	for(int j=0;j<3;j++)
        printf("%d",arr[j]);

}
