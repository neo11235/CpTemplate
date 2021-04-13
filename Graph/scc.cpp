

/**kosaraju's algorithm***/
Graph G;
Graph Gr;
vi vis;
stack<int> order;
void dfs1(int node)
{
    vis[node]=1;
    for(auto e:Gr[node])
        if(!vis[e])
            dfs1(e);
    order.push(node);
}
void dfs2(int node,int color)
{
    vis[node]=color;
    for(auto e:G[node])
        if(!vis[e])
            dfs2(e,color);
}

/***************************/
/****tarjan's***************/
Graph G;

vi vis;
vi dis;
vi low;
vi cstack;
stack<int> sstack;
int curTime=0;
int sccCount=1;
vi sccId;
void tarjansDfs(int node)
{
    vis[node]=cstack[node]=1;
    sstack.push(node);
    dis[node]=low[node]=++curTime;
    for(auto e:G[node])
    {
        if(vis[e])
        {
            if(cstack[e])
            {
                low[node]=min(low[node],low[e]);
            }
            continue;
        }
        tarjansDfs(e);
        low[node]=min(low[node],low[e]);
    }
    if(low[node]==dis[node])
    {
        while(sstack.top()!=node)
        {
            sccId[sstack.top()]=sccCount;
            cstack[sstack.top()]=0;
            sstack.pop();
        }
        sccId[sstack.top()]=sccCount;
        cstack[sstack.top()]=0;
        sstack.pop();
        ++sccCount;
    }
}
void initTarjans(int n)// assuming G is initialized
{
    vis.assign(n,0);
    dis.resize(n);
    low.resize(n);
    cstack.resize(n);
    sstack=stack<int>();
    curTime=0;
    sccCount=1;
    sccId.assign(n,0);
    int i;
    for(i=0;i<n;i++)
    {
        if(!vis[i])
        {
            tarjansDfs(i);
        }
    }
}
