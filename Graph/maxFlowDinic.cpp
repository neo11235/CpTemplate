#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define LSB(i) ((i)&(-i))
#define pii pair<int,int>
#define vi vector<int>
#define triple pair<pair<int,int>,int>
#define vpii vector<pii >
#define Graph vector<vector<int> >
#define WGraph vector<vector<pii>>
#define pli pair<ll,int>
#define pll pair<ll,ll>

#define sci1(a) scanf("%d",&a)
#define sci2(a,b) scanf("%d %d",&a,&b)
#define sci3(a,b,c) scanf("%d %d %d",&a,&b,&c)
#define scs(s) scanf("%s",s)
#ifndef GET_MACRO

#define GET_MACRO(__1,__2,__3,NAME,...) NAME

#endif // GET_MACRO

#define sci(...) GET_MACRO(__VA_ARGS__,sci3,sci2,sci1)(__VA_ARGS__)

#define read freopen("input.txt","r",stdin)
#define write freopen("output.txt","w",stdout)
#define infl 0xfffffffffffffffll
#define infi  0x1fffffff
#define mp(a,b) make_pair(a,b)

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define bound(i,j,n,m) ((i)<n&&(j)<m&&(i)>=0&&(j)>=0)

struct FlowEdge{
    int u,v;
    ll capacity,flow=0;
    FlowEdge(int u,int v,ll capacity):u(u),v(v),capacity(capacity){}
};
struct Dinic
{
    const ll infFlow=1e18;
    vector<FlowEdge> edges;
    vector<vector<int> > g;
    int n,m=0;
    int s,t;
    vector<int> level,ptr;
    queue<int> q;
    Dinic(int n,int s,int t):n(n),s(s),t(t)
    {
        g.resize(n);
        level.resize(n);
        ptr.resize(n);
    }
    void addEdge(int u,int v,ll capacity)
    {
        edges.emplace_back(u,v,capacity);
        edges.emplace_back(v,u,0);
        g[u].push_back(m);
        g[v].push_back(m+1);
        m+=2;
    }
    bool bfs()
    {
        while(!q.empty())
        {
            int node=q.front();
            q.pop();
            for(auto e:g[node])
            {
                if(edges[e].capacity-edges[e].flow<1)
                    continue;
                if(level[edges[e].v]!=-1)
                    continue;
                level[edges[e].v]=level[edges[e].u]+1;
                q.push(edges[e].v);
            }
        }
        return level[t]!=-1;
    }
    ll dfs(int u,ll pushed)
    {
        if(pushed==0)
            return 0;
        if(u==t)
            return pushed;
        for(int &cid=ptr[u];cid<(int)g[u].size();cid++)
        {
            int id=g[u][cid];
            int v=edges[id].v;
            if(level[u]+1!=level[v]||edges[id].capacity-edges[id].flow<1)
                continue;
            ll tr=dfs(v,min(pushed,edges[id].capacity-edges[id].flow));
            if(tr==0)
                continue;
            edges[id].flow+=tr;
            edges[id^1].flow-=tr;
            return tr;
        }
        return 0;
    }
    ll maxFlow()
    {
        ll mF=0;
        while(true)
        {
            fill(level.begin(),level.end(),-1);
            fill(ptr.begin(),ptr.end(),0);
            level[s]=0;
            q.push(s);
            if(!bfs())
                break;
            while(ll pushed=dfs(s,infFlow))
            {
                mF+=pushed;
            }
        }
        return mF;
    }
};


struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap,long long rcap=0) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, rcap);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};
