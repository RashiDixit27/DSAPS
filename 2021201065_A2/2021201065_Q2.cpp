#include <iostream>
#include <sstream>
#include <vector>
#include <typeinfo>
#define M 199
#define POS 67
using namespace std;
template<class T, class V>
class Unordered_map {
    public:
    class Node
    {
        public:
        T key;
        V val;
        Node* next;
        
        Node(T key,V val)
        {
            this->key=key;
            this->val=val;
            next=NULL;
        }
        
    };
    Node * arr[M];   
    Unordered_map(){
        for(int i=0;i<M;i++)
            arr[i]=NULL;
    }
    long long hash_val(string str)
    {
        long long n=str.length();
        long long num=0;
        long long pos_val=1;
        for(long long i=0;i<n;i++)
        {
            num = num + pos_val * str[i];
            num=num%M;
            pos_val*=POS;
        }
        return num;
        
    }
    
    
    void insert(T keyy,V value)
    {
        string str;
        stringstream ss;
        ss<<keyy;
        ss>>str;
        long long hv=hash_val(str);
        Node * ptr = new Node(keyy,value);
        Node * temp= arr[hv];
        int f=0;
        if(temp==NULL)
        {
            arr[hv]=ptr;
        }
        else
        {
            while(temp->next!=NULL)
            {
                if(temp->key==keyy)
                {
                    temp->val=value;
                    f=1;
                }
                temp=temp->next;
            }
            if(temp->key==keyy)
            {
                    temp->val=value;
                    f=1;
            }
            if(f!=1)
                temp->next=ptr;
        }
        return;
    }


    void erase(T keyy)
    {
        string str;
        stringstream ss;
        ss<<keyy;
        ss>>str;
        long long hv=hash_val(str);
        Node * head= arr[hv];
        Node * temp= arr[hv];
        if(head==NULL)
        {
            return;
        }
        if(head->key==keyy)
        {
            head=head->next;
            arr[hv]=head;
        }
        else
        {
            Node * prev=temp;
            while (temp != NULL && temp->key != keyy)
            {
                prev = temp;
                temp = temp->next;
            }
            if(temp != NULL)
                prev->next=temp->next;
            
        }
        return;
    }
    
    bool find(T keyy)    
    {
        string str;
        stringstream ss;
        ss<<keyy;
        ss>>str;
        long long hv=hash_val(str);
        Node * temp= arr[hv];
      

        while (temp != NULL)
        {
            if(temp->key==keyy)
                return true;
            temp = temp->next;
        }
            
        return false;
    }  
    V operator[](T keyy)
    {
        string str;
        stringstream ss;
        ss<<keyy;
        ss>>str;
        long long hv=hash_val(str);
        Node * temp= arr[hv];
        while (temp != NULL)
        {
            if(temp->key==keyy)
                return temp->val;
            temp = temp->next;
        }
        stringstream ss1;
        V temp1;
        if(string(typeid(V).name())=="i")
        {
            ss1<<0;
        }
        else if(string(typeid(V).name())=="f")
        {   
            ss1<<0.00;
        }
        else if(string(typeid(V).name())=="d")
        {
            ss1<<0.00;
        }
        else if(string(typeid(V).name())=="c")
        {
            ss1<<' ';
        }
        else if(string(typeid(V).name())=="b")
        {
            ss1<<false;
        }
        else
        {
            ss1<<"";
        }
        ss1>>temp1;
        insert(keyy,temp1);
        return temp1;
    }
    
    
};
template <typename A>
vector <int> solve(A * arr,int n,int k)
{
     Unordered_map <A,int> mp;
     vector <int> v;
     if(k>n)
        return v;
        int count=0;
        for(int i=0;i<k&&i<n;i++)
        {
            mp.insert(arr[i],mp[arr[i]]+1);
            if(mp[arr[i]]==1)
                count++;
        }
        v.push_back(count);
        for(int i=k;i<n;i++)
        {
            
            mp.insert(arr[i],mp[arr[i]]+1);
            if(mp[arr[i]]==1)
                count++;
            mp.insert(arr[i-k],mp[arr[i-k]]-1);
            if(mp[arr[i-k]]==0)
            {
                count--;
            }
            v.push_back(count);
        }
        
        return v;
}


int main() {
	// your code goes here

	double arr[] ={1.4,3,2,3,4.2,2,5.0,3,6,5.0};
	int arrSize = sizeof(arr)/sizeof(arr[0]);
	int k=5;
	vector <int> v=solve(arr,arrSize,k);
	for(int i=0;i<v.size();i++)
	    cout<<v[i]<<" ";
	cout<<"\n";
	
	Unordered_map <string,int> ob;
	ob.insert("35",55);
	ob.insert("34.1",99.55);
	ob.insert("3.220",55.44);
	ob.insert("3.220",9.3);
	ob.insert("112",3.2);
	ob.insert("35.220",12);
	ob.insert("-22",2.9);
	ob.insert("22.55",45);
	ob.insert("35.22",11);
	ob.insert("0.2",11);
	ob.insert("t",44);

	cout<<"\n";
	ob.erase("-22");
	ob.erase("-22");
	ob.erase(".2");
	ob.erase("112");
	ob.erase("35.220");
	ob.insert("-22",44);
	ob.insert("-22",41.1);

	cout<<ob.find("-22")<<"\n";
	cout<<ob.find("35.220")<<"\n";
	cout<<ob.find("35")<<"\n";
	cout<<ob.find("3.220")<<"\n";
	cout<<ob["-22"]<<"\n";
	cout<<ob["azc"]<<"\n";
	cout<<ob.find("azc")<<"\n";
	cout<<"\n";

	return 0;
}
