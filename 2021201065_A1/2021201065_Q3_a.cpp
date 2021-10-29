#include <iostream>
using namespace std;

const int ROW_SIZE1=3;
const int COL_SIZE1=3;
const int ROW_SIZE2=3;
const int COL_SIZE2=3;

template <typename T>
class three_tupple_matrix
{
    
public:
void transpose(T arr[ROW_SIZE1][COL_SIZE1])
{
    int m=ROW_SIZE1;
    int n=COL_SIZE1;
 
	int count = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (arr[i][j] != 0)
				count++;
		}
	}

	int ele = count+1;
	
	T * a=(T *) malloc(ele * 3 * sizeof(T) );
	a[0] = m;
	a[1] = n;
	a[2] = count;
	int k1 = 3;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (arr[i][j] != 0)
			{
				a[k1++] = i;
				a[k1++] = j;
				a[k1++] = arr[i][j];

			}
		}
	}
	

	T atran[ele*3];
	atran[0] = a[1];
	atran[1] = a[0];
	atran[2] = a[2];
	ele--;
	if (ele > 0)
    {
	int y = 1, k = 3, pos;
	for (int i = 0; i < n; i++)
	{
		for (y = 1; y <= ele; y++)
		{
			pos = y * 3 + 1;
			if (a[pos] == i)
			{
				atran[k++] = a[pos];
				atran[k++] = a[pos - 1];
				atran[k++] = a[pos + 1];
			}
		}
	}
    }
	for (int i = 0; i < (ele+1); i++)
	{
	    cout << atran[i*3] <<"   "<<atran[(i*3)+1]<<"   "<<atran[(i*3)+2];
	    cout<<"\n";
	}
    cout<<"\n";
	return;
}

void addition(T  arr1[ROW_SIZE1][COL_SIZE1], T arr2[ROW_SIZE2][COL_SIZE2])
{
    int m1=ROW_SIZE1;
    int m2=ROW_SIZE2;
    int n1=COL_SIZE1;
    int n2=COL_SIZE2;
	if (m1 != m2 || n1 != n2)
	{
		cout << "Matrices can't be added. \n";
		return;
	}
	
	
	 int count1 = 0;
	for (int i = 0; i < m1; i++)
	{
		for (int j = 0; j < n1; j++)
		{
			if (arr1[i][j] != 0)
				count1++;
		}
	}
	
	
	T * a1=(T*) malloc((count1+1) * 3 * sizeof(T) );
	a1[0] = m1;
	a1[1] = n1;
	a1[2] = count1;
	int k1 = 3;
	for (int i = 0; i < m1; i++)
	{
		for (int j = 0; j < n1; j++)
		{
			if (arr1[i][j] != 0)
			{
				a1[k1++] = i;
				a1[k1++] = j;
				a1[k1++] = arr1[i][j];

			}
		}
	}
	
	
	int count2 = 0;
	for (int i = 0; i < m2; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			if (arr2[i][j] != 0)
				count2++;
		}
	}
	
	T * a2=(T*) malloc((count2+1) * 3 * sizeof(T) );
	a2[0] = m2;
	a2[1] = n2;
	a2[2] = count2;
	int k2 = 3;
	for (int i = 0; i < m2; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			if (arr2[i][j] != 0)
			{
				a2[k2++] = i;
				a2[k2++] = j;
				a2[k2++] = arr2[i][j];

			}
		}
	}
	


	int totsize = a1[2] + a2[2];
	//cout<<totsize;
	T addmtx [((totsize + 1) * 3)] ;
	
	int ele=1, i = 3, j = 3, k = 3,ra1 ,ca1 ,flaga1=1 , ra2, ca2,  flaga2 = 1;
	T dataa1,dataa2;
	while (ele <= totsize)
	{
		if (i < (a1[2]+1) * 3)
		{
			ra1 = a1[i];
			ca1 = a1[i+1];
			dataa1 = a1[i+2];
		}
		else
			flaga1 = 0;

		if (j < (a2[2]+1) * 3)
		{
			ra2 = a2[j];
			ca2 = a2[j+1];
			dataa2 = a2[j+2];
		}
		else
			flaga2 = 0;
		
		if (flaga1 && flaga2)
		{
			if (ra1 == ra2)
			{
				if (ca1 == ca2)
				{
					addmtx[k++] = ra1;
					addmtx[k++] = ca1;
					addmtx[k++] = dataa1 + dataa2;
					i += 3;
					j += 3;
					ele += 2;
				}
				if (ca1 < ca2)
				{
					addmtx[k++] = ra1;
					addmtx[k++] = ca1;
					addmtx[k++] = dataa1;
					i += 3;
					ele++;
				}
			    if (ca1 > ca2)
				{
					addmtx[k++] = ra2;
					addmtx[k++] = ca2;
					addmtx[k++] = dataa2;
					j += 3;
					ele++;
				}
			}
			if (ra1 < ra2)
			{
				addmtx[k++] = ra1;
				addmtx[k++] = ca1;
				addmtx[k++] = dataa1;
				i += 3;
				ele++;
			}
			if (ra1 > ra2)
			{
				addmtx[k++] = ra2;
				addmtx[k++] = ca2;
				addmtx[k++] = dataa2;
				j += 3;
				ele++;
			}
		}
		else if (!flaga1)
		{
			addmtx[k++] = ra2;
			addmtx[k++] = ca2;
			addmtx[k++] = dataa2;
			//cout<<dataa2;
			j += 3;
			ele++;
		}
		else
		{
			addmtx[k++] = ra1;
			addmtx[k++] = ca1;
			addmtx[k++] = dataa1;
			i += 3;
			ele++;
		}
	}
	addmtx[0] = m1;
	addmtx[1] = n1;
	addmtx[2] = (k/3)-1;

	for (int itr = 0; itr < k/3; itr++)
	{
	    cout << addmtx[itr*3]<<"   "<< addmtx[(itr*3)+1]<<"   "<< addmtx[(itr*3)+2]<<"   ";
	    cout<<"\n";
	} 
	cout<<"\n";
	return;
}	


void multiplication(T  arr1[ROW_SIZE1][COL_SIZE1],  T  arr2[ROW_SIZE2][COL_SIZE2])
{
    int m1=ROW_SIZE1;
    int m2=ROW_SIZE2;
    int n1=COL_SIZE1;
    int n2=COL_SIZE2;
    
    
    if ( n1 != m2)
	{
		cout << "Matrices can't be multiplied. \n";
		return;
	}
    
    
    int count1 = 0;
	for (int i = 0; i < m1; i++)
	{
		for (int j = 0; j < n1; j++)
		{
			if (arr1[i][j] != 0)
				count1++;
		}
	}
	
	
	T * a1=(T*) malloc((count1+1)* 3 * sizeof(T) );
	a1[0] = m1;
	a1[1] = n1;
	a1[2] = count1;
	int k1 = 3;
	for (int i = 0; i < m1; i++)
	{
		for (int j = 0; j < n1; j++)
		{
			if (arr1[i][j] != 0)
			{
				a1[k1++] = i;
				a1[k1++] = j;
				a1[k1++] = arr1[i][j];

			}
		}
	}
	
	
	int count2 = 0;
	for (int i = 0; i < m2; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			if (arr2[i][j] != 0)
				count2++;
		}
	}
	
	T * a2=(T*) malloc((count2+1) * 3 * sizeof(T) );
	a2[0] = m2;
	a2[1] = n2;
	a2[2] = count2;
	int k2 = 3;
	for (int i = 0; i < m2; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			if (arr2[i][j] != 0)
			{
				a2[k2++] = i;
				a2[k2++] = j;
				a2[k2++] = arr2[i][j];

			}
		}
	}
	
	
	
	T prod[ROW_SIZE1 * COL_SIZE2 *3];
	int k=3,fa=0,pos=3;
	T sum=0;
    for(int i=0;i<a1[0];i++)
	{
	    
	        for(int j=0;j<a2[1];j++)
	        {
	            fa=0;
	            for(int p=1;p<=a1[2];p++)   
	            {
	                if(a1[p*3]==i)
	                {
	                    pos=p*3;
	                    fa=1;
	                    break;
	                }
	            }     
	            
	            
	        sum=0;
	        
	        if(fa==1)
	        {
	        while(a1[pos]==i )
	        {
	            for(int l=1;l<=a2[2];l++)
	            {
	                if(a2[l*3]==a1[pos+1] && a2[(l*3)+1]== j )
	                sum+=(a1[pos+2]*a2[(l*3)+2]);
	            }
	            pos+=3;  
	        }
	        if(sum!=0)
	        {
	            prod[k++]=i;
	            prod[k++]=j;
	            prod[k++]=sum;
	        }
	        
	    
	   }
	 
	}
	}
	prod[0] = a1[0];
	prod[1] = a2[1];
	prod[2] = (k/3)-1;
	
	for(int i=0;i<= prod[2];i++)
	{
	    cout << prod[i*3]<<"   "<< prod[(i*3)+1]<<"   "<< prod[(i*3)+2]<<"   "<<"\n";
	    
	} 

	cout<<"\n";

}
	


};



int main()
{
	double arr1[ROW_SIZE1][COL_SIZE1] = { 0,9.3,9.9,0,3.22,0,0,2,1};
	double arr2[ROW_SIZE2][COL_SIZE2] = { 1,0,2.2,0,0,3,4,4,5};
	three_tupple_matrix <double>ob1;
    	ob1.transpose(arr1);
	ob1.multiplication(arr1,arr2);
	ob1.addition(arr1,arr2);
	return 0;
}




