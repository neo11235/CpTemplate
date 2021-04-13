Graph G;
int up[200001][20];
int l=19;
vi tin,tout;
int curTime=0;
void dfs(int node,int p)
{
    tin[node]=curTime++;
    up[node][0]=p;
    for(int i=1;i<=l;i++)
    {
        up[node][i]=up[up[node][i-1]][i-1];
    }
    for(auto e:G[node])
    {
        if(e==p)
            continue;
        dfs(e,node);
    }
    tout[node]=curTime++;
}

bool isAncestor(int u,int v)
{
    return tin[u]<=tin[v]&&tout[u]>=tout[v];
}
int lca(int u,int v)
{
    if(isAncestor(u,v))
        return u;
    if(isAncestor(v,u))
        return v;
    for(int k=l;k>=0;k--)
    {
        if(!isAncestor(up[u][k],v))
            u=up[u][k];
    }
    return up[u][0];
}
