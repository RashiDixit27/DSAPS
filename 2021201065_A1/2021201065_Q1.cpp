#include <iostream>
using namespace std;
class BigIntLibrary
{
public:
char compare(string str1,string str2)
{
    if(str1.size() < str2.size())
    {
        return 's';
    }
    else if(str1.size() > str2.size())
    {
        return 'g';
    }
    else
    {
        int index = 0;
        
        while(index < str1.size())
        {
            if(str1[index] < str2[index])
            {
                return 's';
            }
            else if(str1[index] > str2[index])
            {
                return 'g';
            }
            
            index++;
        }
    }
    return 'e';
}  
  

void reverse(string & str)
{
    int n = str.length();
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}

string addition(string str1, string str2)
{
        string res="";
        int size1=str1.length()-1;
        int size2=str2.length()-1;
        int carry=0;
        int k=0;
        while(size1>=0 || size2 >=0)
        {
            int sum =0;
            sum+=carry;
            if(size1 >=0)
            {
                
                sum = sum + str1[size1]-'0';
                size1--;
            }
            if(size2 >=0)
            {
                sum = sum + str2[size2]-'0';
                size2--;
            }
           
            res +=(sum%10 + '0');
            carry= sum/10;   
        }
        if(carry !=0)
        res += (carry +'0');
        reverse(res);
        return res;
}

string difference(string str1,string str2) 
{

    string temp="";
    string res="";
    int f=0;
    int size1=str1.length()-1;
    int size2=str2.length()-1;
    reverse(str1);
    reverse(str2);
    int carry=0;
    for(int i=0;i<=size2;i++)
    {
        if(str1[i]>=str2[i]+carry)
        {
            temp+=(str1[i]-str2[i] +'0'-carry);
            carry=0;
        }
        else
        {
          
          temp+=(str1[i]-str2[i]+10 +'0'-carry);
          carry=1;
        }
    }
    size2++;
    for(int i=size2;i<=size1;i++)
    {
        if(str1[i]>=carry+'0')
        {
            temp+=(str1[i] -carry);
            carry=0;
        }
        else
        {
          
          temp+=(str1[i]+10 -carry);
          carry=1;
        }
    }    
    reverse(temp);
    for(int i=0;i<temp.size();i++)
        {
            if(temp[i]!='0' || f)
            {
                res+= (temp[i]);
                f=1;
            }
        }
    
    return res;
}

string multiply(string str1, string str2) 
{
        string res="";
        int size1=str1.length()-1;
        int size2=str2.length()-1;
        int n=size1+size2+2;
        int f=0;
        int * arr = (int*)malloc(sizeof(int) * (n));
        for(int i=0;i<n;i++)
        {
            arr[i]=0;
            
        }
        
        int dig;
        for(int i=size1;i>=0;i--)
        {
          for(int j=size2;j>=0;j--)
          {
              dig=(str1[i]-'0')*(str2[j]-'0');
              dig=arr[i+j+1]+dig;
              arr[i+j]+=(dig/10);
              arr[i+j+1] =(dig%10);
                           
          }
            
        }
        
        for(int i=0;i<n;i++)
        {
            if(arr[i]!=0 || f)
            {
                res+= (arr[i]+'0');
                f=1;
            }
        }
        free(arr);
        if(res.length()==0)
            return "0";
        
        return res;
    }

string factorial(string str)
{
    string prod="1",temp="1";
    str=addition(str,"1");
    while(!(str==temp))
    {
        prod=multiply(prod,temp);
        temp=addition(temp,"1");
    }
    return prod;
}

string gcd(string str1,string str2)
{
    if(str1=="0" )
        return str2;
    if(str2=="0" )
        return str1;
    if(str1==str2)
        return str1;
    char ch=compare(str1,str2);
    if(ch=='s')
    {
        string temp=str1;
        str1=str2;
        str2=temp;
    }
    return gcd(difference(str1,str2),str2);
}

string exponentiation(string str,long long exp)
{
  string res="1";
  for(long long i=0;i<exp;i++) 
  {
      res=multiply(res,str);
  }
  return res;
}
};
int main() {
	BigIntLibrary ob;
	cout<<ob.difference("0001000","6")<<"\n";
	cout<<ob.addition("999","6")<<"\n";
	cout<<ob.factorial("100")<<"\n";
	cout<<ob.gcd("1111111111","2222222222")<<"\n";
    cout<<ob.exponentiation("2",10000)<<"\n"	;  
    cout<<ob.multiply(ob.difference(ob.addition("9990","6"),"1000"),"8875353");	
    	
	return 0;
}
