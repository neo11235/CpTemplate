

/***********most basic*************/
#define MAX_SZ 500
ll capacity[MAX_SZ][MAX_SZ];
Graph g;
ll bfs(int s,int t,vi &parent)
{
    fill(parent.begin(),parent.end(),-1);
    parent[s]=-2;
    queue<pair<int,ll>> q;
    q.push(mp(s,infi));
    while(!q.empty())
    {
        int node=q.front().first;
        ll nflow=q.front().second;
        q.pop();
        for(auto e:g[node])
        {
            if(parent[e]==-1&&capacity[node][e])
            {
                parent[e]=node;
                ll nnflow=min(nflow,capacity[node][e]);
                if(e==t)
                    return nnflow;
                q.push(mp(e,nnflow));
            }
        }
    }
    return 0;
}
ll max_flow(int s,int t,int n)
{
    ll flow=0;
    vector<int> parent(n);
    int nflow;
    while(nflow=bfs(s,t,parent))
    {
        flow+=nflow;
        int cur=t;
        while(cur!=s)
        {
            int p=parent[cur];
            capacity[p][cur]-=nflow;
            capacity[cur][p]+=nflow;
            cur=p;
        }
    }
    return flow;
}
/**************************************************/
