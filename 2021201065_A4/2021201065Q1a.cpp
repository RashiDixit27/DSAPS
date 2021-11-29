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

void minlexrotation(string str)
{
    int len = str.length();
    string temp = str+str;
    vector <int> suffixarr = suffixArray(temp);
    
    int minind;
    for(int i=0;i<suffixarr.size();i++)
    {
        if(suffixarr[i]<len)
        {
            minind=suffixarr[i];
            break;
        }
    }
    cout<<temp.substr(minind,len)<<"\n";
    return ;
}


int main() {
    string str;
    cout<<"Enter String\n";
    cin>>str;
    minlexrotation(str);
    return 0;
}
