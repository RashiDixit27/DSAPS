#include <iostream>
#include <string>

using namespace std;

class SearchGrid {
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
    
    void dfs(string grid[], int r,int c,int i,int j,node * nav,string op[],int & k)
    {
        if(grid[i][j]=='*')
            return;
        if(nav->next[grid[i][j]-'a']==NULL)
            return;
        nav=nav->next[grid[i][j]-'a'];
        if(nav->word_end==1)
        {
            op[k++]=nav->str;
            int i_sort=k-1;
            string key = op[i_sort];
            int j_sort = i_sort - 1;
            while (j_sort >= 0 && op[j_sort] > key)
            {
                op[j_sort + 1] = op[j_sort];
                j_sort = j_sort - 1;
            }
            op[j_sort + 1] = key;
            nav->word_end=0;
        }
        char temp=grid[i][j];
      
        grid[i][j]='*';
        
        if(i>0)
            dfs(grid,r,c,i-1,j,nav,op,k);
        if(i<r-1)
            dfs(grid,r,c,i+1,j,nav,op,k);
        if(j>0)
            dfs(grid,r,c,i,j-1,nav,op,k);
        if(j<c-1)
            dfs(grid,r,c,i,j+1,nav,op,k); 
        grid[i][j]=temp;
        
    }
    void findWords(string grid[], int r,int c,string words[],string op[],int x) {
        for(int i=0;i<x;i++)
        {
            insertion(words[i]);
        }
        int k=0;
        for(int i=0;i<r;i++)
        {
            for(int j=0;j<c;j++)
            {
                dfs(grid,r,c,i,j,head,op,k);
            }
        }
        for(int i=0;i<k;i++)
        cout<<op[i]<<' ';
        return ;
    }
};


int main() {
    SearchGrid ob;
    int r,c,x;
    cin>>r>>c;
    string grid[r];
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            cin>>grid[i][j];
        }
    }
    cin>>x;
    string words[x];
    string output[x]=words;
   
    for(int i=0;i<x;i++)
    {
        cin>>words[i];
    }
    ob.findWords(grid,r,c,words,output,x);
    return 0;
}
