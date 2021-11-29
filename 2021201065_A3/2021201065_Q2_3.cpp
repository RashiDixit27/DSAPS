#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <algorithm>
#include <climits>
using namespace std;
int shortestPathMatrix(vector<vector<char>> grid,int di,int dj) {
        int m=grid.size(),n=grid[0].size();
        int i=0,j=0;     
        queue <array <int,3>> q;
        if(grid[0][0]==1)
            return -1;
        grid[di][dj]='.';
        q.push({0,0,1});
        while(!q.empty())
        {
            i=q.front()[0];
            j=q.front()[1];
            if(i==di && j==dj)
                return q.front()[2];
            if(i-1>=0 && j>=0 &&  i-1<m && j<n && grid[i-1][j]=='.')
            {
                q.push({i-1,j,q.front()[2]+1});
                grid[i-1][j]=-1;
            }
            if(i>=0 && j-1>=0 &&  i<m && j-1<n && grid[i][j-1]=='.')
            {
                q.push({i,j-1,q.front()[2]+1});
                grid[i][j-1]=-1;
            } 
            if(i>=0 && j+1>=0 &&  i<m && j+1<n && grid[i][j+1]=='.')
            {
                q.push({i,j+1,q.front()[2]+1});
                grid[i][j+1]=-1;
            } 
            if(i+1>=0 && j>=0 &&  i+1<m && j<n && grid[i+1][j]=='.')
            {
                q.push({i+1,j,q.front()[2]+1});
                grid[i+1][j]=-1;
            }
            q.pop();
            
        }
        return -1;
        
}
int main() {
    int n,m;
    cin>>n>>m;
    char ch;
    vector<vector<char>> grid(n-2, vector<char> (m-2));
    vector<pair<int,int>> riders;
    int r=0,c=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cin>>ch;
            if(i!=0 && i!=n-1 && j!=0 && j!=m-1)
            {
                grid[r][c]=ch;
                if(grid[r][c]=='R')
                     riders.push_back({r,c});
                c++;
            }
        }
        if(i!=0 && i!=n-1)
        {
            r++;
            c=0;
        }
    }
    r=(grid.size()-1);
    c=(grid[0].size()-1);
    int dist = shortestPathMatrix(grid,r,c);
    if(dist==-1)
    {
        cout<<"NO"; 
    }
    else
    {
        int rdist;
        int mndist=INT_MAX;
        for(int i=0;i<riders.size();i++)
        {
            rdist=shortestPathMatrix(grid,riders[i].first,riders[i].second);
            if(rdist==-1)
               rdist=INT_MAX; 
            mndist=min(mndist,rdist); 
        }
        if(dist<=mndist)
            cout<<"YES"<<"\n"<<dist;
        else
            cout<<"NO";
    }
    return 0;
}
