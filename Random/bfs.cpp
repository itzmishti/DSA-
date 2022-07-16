#include <bits/stdc++.h>
using namespace std;

//BFS Transversal
vector<int> bfsTrans(vector<int> adj[],int V)
{
    vector<int>vis(V+1,0);
    vector<int>bfs;
    
    for(int i=1;i<=V;i++)
    {
        if(!vis[i])
        {
            queue<int>q;
            q.push(i);
            vis[i]=1;
            while(!q.empty())
            {
                int n=q.front();
                q.pop();
                bfs.push_back(n);
                
                for(auto it:adj[n])
                {
                    if(!vis[it])
                    {
                        q.push(it);
                        vis[it]=1;
                        
                    }
                }
            }
        }
    }
    return bfs;
}

int main()
{
 int e,v;
 cout<<"Enter edges : ";
 cin>>e;
 cout<<"Enter vertices : ";
 cin>>v;
 //adj is our adjency list
 vector<int>adj[v+1];
 
 for(int i=0;i<e;i++)
 {
     int x,y;
     cout<<"Enter the edge";
     cin>>x>>y;
     adj[x].push_back(y);
     adj[y].push_back(x);
     
 }
 for(int i=1;i<=v;i++)
 {
     cout<<i;
     for(auto j: adj[i])
     {
         cout<<"->"<<j;
     }
     cout<<endl;
 }
 
 vector <int> bfs=bfsTrans(adj,v);
 for(auto i:bfs)
 {
     cout<<i<<"->";
 }
    return 0;
}
