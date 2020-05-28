#include<stdio.h>
#include<stdlib.h>

int *yalloc ;

// index to store starting ,end and next free addres
struct index 					
	{	int *s_add;
		int *e_add;
		int *next_add;
		struct index *next;	
	}*top;

// it will return position of address in yalloc buffer
int pos(int *add);

// it will free given variable
void yfree(int *add);

// it will combine two free nodes
void combine();

// malloc function
int *ymalloc(int size);

void disp();

// it will return size difference b/w two address
int difference(int *add,int *b);

void main()
{	yalloc=(int *)malloc(10000*sizeof(int));	
	top=(struct index *)malloc(sizeof(struct index));	
	top->s_add=NULL;
	top->e_add=NULL;
	top->next_add=NULL;	
	top->next=NULL;

	int *a=ymalloc(100);
	int *b=ymalloc(200);
	disp();
	int *c=ymalloc(100);
	int *d=ymalloc(300);
	int *e=ymalloc(500);
	disp();
	yfree(a);
	disp();
	int *f=ymalloc(400);
	disp();
	yfree(c);
	disp();
	int *g=ymalloc(500);	
	disp();
	yfree(d);
	yfree(e);
	int *h=ymalloc(300);
	disp();
	
}

int *ymalloc(int size)
{	struct index * temp  =(struct index*)malloc(sizeof(struct index));	
	struct index * new   =(struct index*)malloc(sizeof(struct index));    
	struct index * np    =(struct index*)malloc(sizeof(struct index));
	struct index * xtra1 =(struct index*)malloc(sizeof(struct index));
	struct index * xtra2 =(struct index*)malloc(sizeof(struct index));	
	
	temp=top;
	int *addr;

	// if starting node if empty
	if(temp->s_add==NULL)
	{
		// if it is not a free node
		if(temp->next==NULL)
		{
			addr=&yalloc[0];
			temp->s_add=&yalloc[0];
			temp->e_add=&yalloc[size-1];
			return addr;
		}
	
		// if it is a free node	
		else
		{	
			// now there are two cases 
			// 1st.. length required is equal to length available
			if(temp->next!=NULL && (pos(temp->next_add)-1)==size)
			{	addr=&yalloc[0];
		                temp->s_add=&yalloc[0];
		                temp->e_add=&yalloc[size-1];
				return addr;
			}
			// 2nd.. length required is greter than length avavilable then allocate and create another node of left free space
		        else if(temp->next!=NULL && (pos(temp->next_add)-1)>size)
		        {       addr=&yalloc[0];
		                temp->s_add=&yalloc[0];
		                temp->e_add=&yalloc[size-1];
		               	new->next_add=temp->next_add;
				temp->next_add=&yalloc[size];
				new->s_add=NULL;
				new->e_add=NULL;
				new->next=temp->next;
				temp->next=new;
				 return addr;
		        }	
		}	
	}
	else
	{

		// if first node is not free 

		// cheack which node is free
		while(temp->next!=NULL)
		{	if(temp->s_add==NULL)
			{ 	
	                        xtra1=top;
        	                while(xtra1->next->next_add!=temp->next_add)
                	                xtra1=xtra1->next;
                       		if(difference(temp->next_add,xtra1->next_add)>=size)
					break;
			}
			
			temp=temp->next;
                }
	
		// if node searched is not a free node
		if(temp->s_add!=NULL)
		{	addr=&yalloc[pos(temp->e_add)];
			
			np->s_add=addr;
			np->e_add=&yalloc[(size-2)+pos(addr)];
			np->next_add=NULL;
			np->next=NULL;
			temp->next=np;
			temp->next_add=np->s_add;	
		}

		// it is a free node
		else
		{	
			xtra2=top;
			while(xtra2->next->next_add!=temp->next_add)
				xtra2=xtra2->next;
			
			// size required is equal to available
			if(difference(temp->next_add,xtra2->next_add)==size)	
			{	addr=&yalloc[pos(xtra2->e_add)];	
				struct index *np=(struct index*)malloc(sizeof(struct index));
        	                np->s_add=addr;
                	        np->e_add=&yalloc[(size-2)+pos(np->s_add)];
                        	np->next_add=NULL;
               	         	np->next=NULL;
                	        temp->s_add=np->s_add;
                        	temp->e_add=np->e_add;
			}
			
			// size is greter than required then allocate and create another node of left free space
			else if(difference(temp->next_add,xtra2->next_add)>size)
			{	addr=&yalloc[pos(xtra2->e_add)];      
                                struct index *np=(struct index*)malloc(sizeof(struct index));
                                np->s_add=addr;
                                np->e_add=&yalloc[(size-2)+pos(addr)];
                                np->next_add=NULL;
                                np->next=NULL;
                                temp->s_add=np->s_add;
                                temp->e_add=np->e_add;
              			new->next_add=temp->next_add;
	                	temp->next_add=&yalloc[size];
        		        new->s_add=NULL;
		                new->e_add=NULL;
              			new->next=temp->next;
		                temp->next=new;
			}
		}
		return addr;
        }	
	
}
void combine()
{	struct index * temp=(struct index*)malloc(sizeof(struct index));
        temp=top;
	while(temp->next!=NULL)
	{
		if(temp->s_add==NULL && temp->next->s_add==NULL)
		
		{	
			temp->next_add=temp->next->next_add;
			temp->next=temp->next->next;	
		}
			
		temp=temp->next;
	}
}
void yfree(int *add)
{	struct index * temp=(struct index*)malloc(sizeof(struct index));	
	temp=top;
	if(top->s_add==add)
	{	top->s_add=NULL;
	        top->e_add=NULL;
	}
	else
	{
		while(temp->next->s_add!=add)
			temp=temp->next;
		if(temp->next->next!=NULL)
		{	temp->next->s_add=NULL;
			temp->next->e_add=NULL;	
		}
		else
			temp->next=NULL;
	}
	combine(); 
}

void disp()
{	struct index * temp=(struct index*)malloc(sizeof(struct index));
        temp=top;
	printf("Start -- End\n\n");
	while(temp->next!=NULL)
	{	if(pos(temp->s_add)!=0)	
			printf("%d --- %d \n",pos(temp->s_add),pos(temp->e_add));
		else
			printf("Free space\n");		
		temp=temp->next;
	}
	if(pos(temp->s_add)!=0)		
	printf("%d --- %d\n\n\n",pos(temp->s_add),pos(temp->e_add));
}


int pos(int *add)
{       int addr;
	int var1=(int) add;
        int var2=(int) &yalloc[0];
        addr=(var1-var2)/4+1;
	if(addr<0)
	return 0;
	else
	return (var1-var2)/4 +1;
}
int difference(int *add,int *b)
{
        int var1=(int) add;
        int var2=(int) b;
        return (var1-var2)/4;
}

