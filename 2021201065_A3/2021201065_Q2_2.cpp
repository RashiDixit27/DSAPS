#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <climits>

using namespace std;

vector<vector<pair<int,int>>> makegraph(vector<vector<int>> edges,int n)
    { 
        vector<vector<pair<int,int>>> graph(n);
        for(int i=0;i<edges.size();i++)
        {
            graph[edges[i][0]].push_back({edges[i][1],edges[i][2]});
            graph[edges[i][1]].push_back({edges[i][0],edges[i][2]});
        }
        return graph;
    }   
void pathStoD(vector<vector<pair<int,int>>> graph,int s ,int  d,vector<pair<int,string>> & pathdistsd ,vector<int> & path,vector<int> & dist,int dis,vector<bool> & visited,int & ind)
{
        visited[s] = true;
        path[ind] = s;
        dist[ind] = dis;
        ind++;        
        vector<int> temp;
        string path_="";
        int distemp=0;
        if (s == d) {
            for (int i = 0; i < ind; i++)
            {             
                path_+=to_string(path[i]);
                path_+=" ";
                distemp+=dist[i];
            }
            pathdistsd.push_back({distemp,path_});
        }
        else 
        {
            for (int i = 0; i < graph[s].size(); i++)
            {
                if (visited[graph[s][i].first]==false)
                    pathStoD(graph,graph[s][i].first,d,pathdistsd,path,dist,graph[s][i].second,visited,ind);
            }
        }
    ind--;
    visited[s] = false;
}
    
    
void allpathStoD(vector<vector<pair<int,int>>> graph,int n,int s,int d,vector<pair<int,string>> & path_dist_sd) {
        vector<bool> visited(n,false);
        vector<int> path(n);
        int ind=0;
        vector<int> dist(n);
        //vector<pair<int,string>> path_dist_sd;  
        pathStoD(graph,s,d,path_dist_sd,path,dist,0,visited,ind);
    
}
void kthshortestpath(vector<vector<pair<int,int>>> graph,int n,int k) 
{
    vector<pair<int,string>> path_dist_sd;  
    
    for(int i=0;i<n-1;i++)
    {
        for(int j=i+1;j<n;j++)
        allpathStoD(graph,n,i,j,path_dist_sd);
    }
    sort(path_dist_sd.begin(),path_dist_sd.end());
    
    for(int i=0;i<min(k,int(path_dist_sd.size()));i++)
        cout<<path_dist_sd[i].second<<"\n";
}


int main() {
	 int n,m,k;
    int v1,v2,dist,s;
    cin>>n>>m;
    vector<vector<int>> edges(m, vector<int> (3));
    for(int i=0;i<m;i++)
    {
        cin>>v1>>v2>>dist;
        edges[i][0]=v1;
        edges[i][1]=v2;
        edges[i][2]=dist;
    }
    cin>>k;
    vector<vector<pair<int,int>>> graph= makegraph(edges,n);
    kthshortestpath(graph,n,k);
    return 0;
}
