#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;
class suffixnode{
    public:
    int ind;
    int r1;
    int r2;
};
bool cmp(suffixnode n1, suffixnode n2)
{
    if(n1.r1<n2.r1)
        return true;
    else if(n1.r1==n2.r1 && n1.r2<n2.r2)
        return true;
    else 
        return false;
}
vector<int> suffixArray(string str)
{
    int len = str.length();
    vector<int> indexcalc(len);
    vector<int> suffixarr(len);
    vector<suffixnode> suffixnodes(len);
    for(int i=0;i<len-1;i++)
    {
        suffixnodes[i].ind=i;
        suffixnodes[i].r1=str[i];
        suffixnodes[i].r2=str[i+1];
    }
    suffixnodes[len-1].ind=len-1;
    suffixnodes[len-1].r1=str[len-1];
    suffixnodes[len-1].r2=-1;
    sort(suffixnodes.begin(),suffixnodes.end(),cmp);

    int ind=4;
    int currank;
    int prevrank;
    while(ind<2*len)
    {
        currank=0;
        indexcalc[suffixnodes[0].ind]=0;
        prevrank=suffixnodes[0].r1;
        suffixnodes[0].r1=0;

        for(int i=1;i<len;i++)
        {
            if(suffixnodes[i].r1==prevrank && suffixnodes[i].r2==suffixnodes[i-1].r2)
            {
                suffixnodes[i].r1=currank;
            }
            else
            {
                currank++;
                prevrank=suffixnodes[i].r1;
                suffixnodes[i].r1=currank;
            }
            indexcalc[suffixnodes[i].ind]=i;
        }
        for(int i=0;i<len;i++)
        {
            int nxtind=suffixnodes[i].ind+ind/2;
            if(nxtind<len)
                suffixnodes[i].r2 = suffixnodes[indexcalc[nxtind]].r1;
            else
                suffixnodes[i].r2 = -1;
        }
        sort(suffixnodes.begin(),suffixnodes.end(),cmp);
        ind*=2;
    }
    for(int i=0;i<len;i++)
        suffixarr[i]=suffixnodes[i].ind;
    return suffixarr;
}

vector<int> longestcommonprefix(vector<int> suffixarr,string str)
{
    int len = suffixarr.size();
    vector<int> lcp(len,0);
    vector<int> indsuffix(len,0);
    int i=0;
    while(i<len)
    {
        indsuffix[suffixarr[i]] = i;
        i++;
    }
    int itr = 0;
    int j;
    for (i=0;i<len;i++)
    {
        if (indsuffix[i] == (len-1))
        {
            itr = 0;
            continue;
        }
        j = suffixarr[indsuffix[i]+1];
        while ((itr+i<len) && (itr+j)<len && str[(itr+i)]==str[(itr+j)])
            itr++;
 
        lcp[indsuffix[i]] = itr; 
        if (itr>0)
            itr--;
    }
    return lcp;
}

int longestsubstrK(string str,int k)
{
    if(k==1)
        return str.length();
    int minlcp;
    vector <int> suffixarr = suffixArray(str);
    vector <int> lcp = longestcommonprefix(suffixarr,str);
    map <int,int> minele;
    int len = lcp.size();
    k--;
    for(int i=0;i<k;i++)
    {
        minele[lcp[i]]++;
    }
    minlcp=minele.begin()->first;
    for(int i=1;i<len-k;i++)
    {
        if(minele[lcp[i-1]]==1)
        {
            minele.erase(lcp[i-1]);
        }
        else
        {
            minele[lcp[i-1]]--;
        }
        minele[lcp[i+k-1]]++;
        minlcp=max(minlcp,minele.begin()->first);
    }
    if(minlcp!=0)
        return minlcp;
    else
        return -1;
}

int main() {
    string str;
    int k;
    cout<<"Enter String\n";
    cin>>str;
    cout<<"Enter k\n";
    cin>>k;
    cout<<longestsubstrK(str,k)<<"\n";
    return 0;
}
