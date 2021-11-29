#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <climits>
using namespace std;

vector<string> shortestpath(int n, vector<vector<int>> edges, int s) {
vector<int> dist(n,INT_MAX);
vector<string> path(n,"");
vector<vector<pair<int,int>>> graph(n);
for(int i=0;i<edges.size();i++)
{
    graph[edges[i][0]].push_back({edges[i][1],edges[i][2]});
    graph[edges[i][1]].push_back({edges[i][0],edges[i][2]});
}
for(int i=0;i<graph.size();i++)
{
    for(int j=0;j<<graph[i].size();j++)
    {
        cout<<graph[i][j].first<<" "<<graph[i][j].second<<"\n";
    }
}
vector <pair<int,int>> visited;
dist[s]=0;
path[s]=to_string(s);
visited.push_back({s,0});
while(!visited.empty())
{
    pair<int,int> visnode=visited[0];
    auto vitr=visited.begin();
    for(auto i=visited.begin();i!=visited.end();i++)
    {
        if(i->second<visnode.second || (i->second==visnode.second && i->first<visnode.first))
        {
            visnode={i->first,i->second};
            vitr=i;
        }
    }
   
    visited.erase(vitr);
    //cout<<visnode.first<<visnode.second<<"\n";
    for(int i=0;i<graph[visnode.first].size();i++)
    {
        //cout<<dist[graph[visnode.first][i].first]<<" "<<dist[visnode.first]+graph[visnode.first][i].second<<'\n';
        if(dist[graph[visnode.first][i].first]>dist[visnode.first]+graph[visnode.first][i].second)
        {
            pair<int,int> p={graph[visnode.first][i].first,dist[graph[visnode.first][i].first]};
            auto itr=find(visited.begin(), visited.end(),p);
            if (itr != visited.end())
                visited.erase(itr);           
            dist[graph[visnode.first][i].first]=dist[visnode.first]+graph[visnode.first][i].second;
            visited.push_back({graph[visnode.first][i].first,dist[graph[visnode.first][i].first]});
            if(path[graph[visnode.first][i].first].length()!=0)
            {
            string tempstr=to_string(graph[visnode.first][i].first);
            tempstr+=" ";
            tempstr+=path[visnode.first];
            path[graph[visnode.first][i].first]=tempstr;
            
            }
            else
            {
                string tempstr=to_string(graph[visnode.first][i].first);
                tempstr+=" ";
                tempstr+=path[visnode.first];
                path[graph[visnode.first][i].first]=tempstr;
            }
        }
        else if(dist[graph[visnode.first][i].first]==dist[visnode.first]+graph[visnode.first][i].second)
        {
            string tempstr=to_string(graph[visnode.first][i].first);
            tempstr+=" ";
            tempstr+=path[visnode.first];
            //cout<<tempstr<<" ";
            if(path[graph[visnode.first][i].first]>tempstr)
            path[graph[visnode.first][i].first]=tempstr;
        }
    }
    
}

return path;
}

int main()
{
    int n,m;
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
    cin>>s;
   
    vector<string> path= shortestpath(n,edges,s);
    for(int i=0;i<path.size();i++)
    {
        if(i!=s)
        cout<<path[i]<<"\n";
    }
    return 0;
       
}