#include <iostream>
using namespace std;

class Trie {
public:
    class node {
        public:
        int ch;
        node * next[2];
        node(int ch)
        {
            this->ch=ch;
            for (int i = 0; i < 2; ++i) 
            {
                next[i] =NULL;
            }
        }
    };
    node * head=new node(-1);
    void insertion(long long num)
    {  
        long long k; 
        node * ptr = head;
        for(int i=45;i>=0;i--)
        {
            k=(num>>i)&1;
            if(ptr->next[k]==NULL) 
            {
                ptr->next[k]=new node(k);
            }
            ptr=ptr->next[k];
        }
    }
    void maxxor(long long query)
    {   
        long long k;
        node * ptr = head;
        long long op=0;
        for(int i=45;i>=0;i--)
        {
            k=(query>>i)&1;
            if(k==1)
                k=0;
            else
                k=1;

            if(!ptr->next[k]) {
                if(k==1)
                    k=0;
                else
                    k=1;
            }
            op=op<<1|k;
            ptr=ptr->next[k];
        }
        cout<<"Max XOR:"<<(op^query)<<"\n";
    }
};
int main()
{
    Trie ob;
    int n,q;
    cin>>n;
    cin>>q;
    long long A[n];
    for(int i=0;i<n;i++)
    {
        cin>>A[i];
        ob.insertion(A[i]);
    }
    long long query;
    for(int i=0;i<q;i++)
    {
        cin>>query;
        ob.maxxor(query);       
        
    }
    return 0;
}
