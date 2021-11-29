#include <iostream>
#include <vector>
using namespace std;

class Trie {
public:
    class node {
        public:
        char ch;
        int word_end;
        node * next[26];
        string str;
        node(char ch)
        {
            this->ch=ch;
            word_end=0;
            for (int i = 0; i < 26; ++i) 
            {
                next[i] =NULL;
            }
        }
    };
    node * head=new node('/');
    void insertion(string s)
    {
        node * nav=head;
        for(int i=0;i<int(s.length());i++)
        {
            if((nav->next[s[i]-'a'])==NULL)
            {
               node * ptr = new node(s[i]); 
               nav->next[s[i]-'a']=ptr; 
            }  
                nav=nav->next[s[i]-'a'];          
        }
        
                nav->str=s;
                nav->word_end=1;
        
    }
    
 
    int spellCheck(string s) {
        
        node * nav=head;
        int f=0;
        for(int i=0;i<int(s.length());i++)
        {
            if((nav->next[s[i]-'a'])==NULL)
            {
                f=1;
                break;
            }  
                nav=nav->next[s[i]-'a'];          
        }
        if(f==0 && nav->word_end==1)
        return 1;
        else
        return 0;
       
    }
    
    void find(node * nav,vector<string> & autocom)
    {
        if(nav->word_end==1)
            {
                autocom.push_back(nav->str);
            }
        for(int i=0;i<26;i++)
        {
            if(nav->next[i]!=NULL)
            {
                find(nav->next[i],autocom); 
            }
            
        }
                
    }
    
    
    vector<string> Autocomplete(string s) {
        node * nav=head;
        int f=0;
        for(int i=0;i<int(s.length());i++)
        {
            if((nav->next[s[i]-'a'])==NULL)
            {
                f=1;
                break;
            }  
                nav=nav->next[s[i]-'a'];          
        }
        vector<string> autocom;
        if(f==0)
        {
            find(nav,autocom);   
        }
        return autocom;
    }
    
    
    void findautocorrect(node * nav,string s,vector <int> dp1,vector<string> & autocorr)
    {
        int n=s.length()+1;
        vector <int> dp2(n);
        dp2[0]=dp1[0]+1;
        for(int j=1;j<n;j++)
        {
            if(nav->ch==s[j-1])
            {
                dp2[j]=dp1[j-1];
            }
            else
            {
                int mn=min(dp1[j-1],dp1[j]);
                mn=min(mn,dp2[j-1]);
                dp2[j]=mn+1;
            }
        
        }
       
        
        if(nav->word_end==1 && dp2[n-1]<=3)
            {
                autocorr.push_back(nav->str);
            }
        for(int i=0;i<26;i++)
        {
            if(nav->next[i]!=NULL)
            {
                findautocorrect(nav->next[i],s,dp2,autocorr);
            }
        }
    }          
    
    
    
    
    vector<string> Autocorrect(string s) {
        node * nav=head;
        int n=s.length()+1;
        vector <int> dp1(n);
        for(int i=0;i<n;i++)
            dp1[i]=i;
        vector<string> autocorr;
        for(int i=0;i<26;i++)
        {
            if(nav->next[i]!=NULL)
            {
                findautocorrect(nav->next[i],s,dp1,autocorr); 
            }
        }    
        return autocorr;
    }
    
    
};

int main() {
	Trie ob;
	int n;
	cin>>n;
	string str;
	for(int i=0;i<n;i++)
	{
	    cin>>str;
	    ob.insertion(str);	    
	}
	int ai;
	cin>>ai>>str;
	vector<string> acom,acorr;
	switch (ai)
    {
       case 1:  cout<<ob.spellCheck(str)<<'\n';
                break;
       case 2:  acom=ob.Autocomplete(str);
                cout<<acom.size()<<'\n';
                for(int i=0;i<acom.size();i++)
                    cout<<acom[i]<<'\n';
                break;
       case 3:  acorr=ob.Autocorrect(str);
                cout<<acorr.size()<<'\n';
                for(int i=0;i<acorr.size();i++)
                    cout<<acorr[i]<<'\n';
                break;
       default: cout<<"Wrong option given\n";
                break; 
    }
	return 0;
}
