#include <iostream>
using namespace std;
const int ROW_SIZE1=3;
const int COL_SIZE1=3;
const int ROW_SIZE2=3;
const int COL_SIZE2=3;


 
template <typename T>
class three_tupple_matrixll
{
    
    public:
    
    
    class node{
    public:
    int row;
    int col;
    T data;
    node * next;
    node(int r,int c,T d)
    {
        row=r;
        col=c;
        data=d;
        next=NULL;
    }
    };
    
    node * head ;
    void transpose(T arr[ROW_SIZE1][COL_SIZE1])
    {
        
        int m=ROW_SIZE1;
        int n=COL_SIZE1;
 
	    int count = 0;
	    node * temp,*ptr;
	    head=NULL;
	    for (int i = 0; i < m; i++)
	    {
		    for (int j = 0; j < n; j++)
		    {
			    if (arr[i][j] != 0)
			    {
			        count++;
			        ptr = new node(i,j,arr[i][j]);
			        if(count==1)
			        {
			            head=ptr;
			            temp=ptr;
			        }
			        else
			        {
			            temp->next=ptr;
			            temp=temp->next;
			        }
			  
			    }
		    }
	    }
	    
	    temp=head;
	    node * headt;
	    node * tempt;
	    //node * ptr;
	    node * tt1;
	    node * tt2;
	    while(temp!=NULL)
	    {
	        ptr =new node(temp->col,temp->row,temp->data);
	        if(headt==NULL)
	        {
	            headt=ptr;
	            
	            }
	        else
	        {
	            tt1=headt;
	            //tt2=headt;
	            int flag=0;
	            while(tt1!=NULL)
	            {
	                if(ptr->row < tt1->row || (ptr->row==tt1->row && ptr->col < tt1->col))
	                {
	                    if(tt1==headt)
	                    {
	                        headt=ptr;
	                        ptr->next=tt1;
	                    }
	                    else
	                    {
	                        tt2->next=ptr;
	                        ptr->next=tt1; 
	                    }
	                    flag=1;
	                    break;
	                }
	                else
	                {
	                    tt2=tt1;
	                    tt1=tt1->next;
	                }
	            }
	    
	            if (flag==0)
	            {
	                tt2->next=ptr;
	            }
	        }
	        temp=temp->next;
        }
         
         temp=headt;
         while(temp!=NULL)
	    {
	        cout <<temp->row<< " "<<temp->col<< " "<<temp->data<< " \n";
	        temp=temp->next;
	    }
    } 
    
    void add_matrix(T arr1[ROW_SIZE1][COL_SIZE1], T arr2[ROW_SIZE1][COL_SIZE1])
    {
        int m=ROW_SIZE1;
        int n=COL_SIZE1;
 
	    int count = 0;
	    node * heada, *headb;
	    node * temp,*ptr;
	    heada=NULL;
	    headb=NULL;
	    for (int i = 0; i < m; i++)
	    {
		    for (int j = 0; j < n; j++)
		    {
			    if (arr1[i][j] != 0)
			    {
			        count++;
			        ptr = new node(i,j,arr1[i][j]);
			        if(count==1)
			        {
			            heada=ptr;
			            temp=ptr;
			        }
			        else
			        {
			            temp->next=ptr;
			            temp=temp->next;
			        }
			  
			    }
		    }
	    }
	    
	    temp=NULL;
	    ptr=NULL;
	    count = 0;

	    for (int i = 0; i < m; i++)
	    {
		    for (int j = 0; j < n; j++)
		    {
			    if (arr2[i][j] != 0)
			    {
			        count++;
			        ptr = new node(i,j,arr2[i][j]);
			        if(count==1)
			        {
			            headb=ptr;
			            temp=ptr;
			        }
			        else
			        {
			            temp->next=ptr;
			            temp=temp->next;
			        }
			  
			    }
		    }
	    }
	    
	    node * tempa,*tempb,*tempc,*headc;
	    ptr=NULL;
	    headc=NULL;
	    tempa=heada;
	    tempb=headb;
	    tempc=headc;
	    
	 //   if (headb==NULL)
	  //      cout<< "NULL\n";
	    
	    while (tempa!=NULL || tempb!=NULL )
	    {
	        if (tempa==NULL)
	        {
	            while (tempb!=NULL)
	            {
	                ptr = new node(tempb->row,tempb->col,tempb->data);
	                if (tempc==NULL)
	                {
	                    headc=ptr;
	                }
	                else 
	                {
	                    tempc->next=ptr;
	                }
	                tempc=ptr;
	                tempb=tempb->next;
	            }
	        }
	        else if (tempb==NULL)
	        {
	           while (tempa!=NULL)
	            {
	                ptr = new node(tempa->row,tempa->col,tempa->data);
	                if (tempc==NULL)
	                {
	                    headc=ptr;
	                }
	                else 
	                {
	                    tempc->next=ptr;
	                }
	                tempc=ptr;
	                tempa=tempa->next;
	            } 
	        }
	        else if  ((tempa->row < tempb->row) || ((tempa->row == tempb->row) && (tempa->col < tempb->col)))
	       {
	            ptr = new node(tempa->row,tempa->col,tempa->data);
	            if (tempc==NULL)
	            {
	                headc=ptr;
	            }
	            else 
	            {
	                tempc->next=ptr;
	            }
	            tempc=ptr;
	            tempa=tempa->next;
	        }
	        
	       
	        else if ((tempa->row > tempb->row) || ((tempa->row == tempb->row) && (tempa->col > tempb->col)))
	        {
	            ptr = new node(tempb->row,tempb->col,tempb->data);
	            if (tempc==NULL)
	            {
	                headc=ptr;
	            }
	            else 
	            {
	                tempc->next=ptr;
	            }
	            tempc=ptr;
	            tempb=tempb->next;
	        }
	        else if ((tempa->row == tempb->row) && (tempa->col == tempb->col))
	        {
	            ptr = new node(tempa->row,tempa->col,tempa->data+tempb->data);
	            if (tempc==NULL)
	            {
	                headc=ptr;
	            }
	            else 
	            {
	                tempc->next=ptr;
	            }
	            tempc=ptr;
	            tempa=tempa->next;
	            tempb=tempb->next; 
	        }
	        
	      /* */  
	    }
	     tempc=headc;
	     cout <<"\nAdd Matrix\n";
         while(tempc!=NULL)
	    {
	        cout <<tempc->row<< " "<<tempc->col<< " "<<tempc->data<< " \n";
	        tempc=tempc->next;
	    }
	    
        
   }
    
};
int main() 
{
	// your code goes here
	double arr[ROW_SIZE1][COL_SIZE1]={1,44,0,7.5,0,2,5.5,0,90};
	double arr1[ROW_SIZE1][COL_SIZE1]={0,1,3.03,4,5,6.33,7,8.3,9};
	double arr2[ROW_SIZE1][COL_SIZE1]={10,11.5,12.6,13,14,15.45,16,17,18.19};
	three_tupple_matrixll <double>ob1;
	ob1.transpose(arr);
	ob1.add_matrix(arr1, arr2);
	return 0;
}