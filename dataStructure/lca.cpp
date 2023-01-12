namespace LCA{
    const int max_size=400000;
    const int len=20;
    int up[max_size][len+1];
    int min_[max_size][len+1];
    int max_[max_size][len+1];
    int tin[max_size];
    int tout[max_size];
    int timer;
    vector<vector<pii > > G;
    void DFS(int node,int parent,int cost);
    void init()
    {
        int n=G.size();
        memset(tin,0,sizeof(tin));
        memset(tout,0,sizeof(tout));
        timer=0;
        for(int i=0;i<n;++i)
        {
            if(!tin[i])
                DFS(i,i,0);
        }
    }
    void DFS(int node,int parent,int cost){
        tin[node]=++timer;
        up[node][0]=parent;
        min_[node][0]=cost;
        max_[node][0]=cost;
        int i;
        for(i=1;i<=len;i++){
            up[node][i]=up[up[node][i-1]][i-1];
            min_[node][i]=min(min_[node][i-1],min_[up[node][i-1]][i-1]);
            max_[node][i]=max(max_[node][i-1],max_[up[node][i-1]][i-1]);
        }
        for(i=0;i<G[node].size();i++){
            if(G[node][i].first!=parent)DFS(G[node][i].first,node,G[node][i].second);
        }
        tout[node]=++timer;
        return;
    }
    bool is_ancestor(int u,int v){//if u is an ancestor of v
        return tin[u]<=tin[v]&&tout[u]>=tout[v];
    }
    int lca(int u,int v){
        if(is_ancestor(u,v))return u;
        if(is_ancestor(v,u))return v;
        for(int i=len;i>=0;i--){
            if(!is_ancestor(up[u][i],v))u=up[u][i];
        }
        return up[u][0];
    }
    int min_road(int u,int p){//p must be ancestor of u
        int rval=INT_MAX;
        int i=len;
        while(i>=0){
            if(u==p)break;
            if(up[u][i]==p)return min(rval,min_[u][i]);
            if(is_ancestor(up[u][i],p)){
                i--;
            }
            else{
                rval=min(min_[u][i],rval);
                u=up[u][i];
            }
        }
        return rval;
    }
    int max_road(int u,int p){
        int rval=INT_MIN;
        int i=len;
        while(i>=0){
            if(u==p)break;
            if(up[u][i]==p)return max(rval,max_[u][i]);
            if(is_ancestor(up[u][i],p)){
                i--;
            }
            else{
                rval=max(rval,max_[u][i]);
                u=up[u][i];
            }
        }
        return rval;
    }
}
///just lca O(logn)
namespace LCA{
    const int max_size=400000;
    const int len=20;
    int up[max_size][len+1];
    int tin[max_size];
    int tout[max_size];
    int timer;
    vector<vector<int > > g;
    void DFS(int node,int parent);
    void init()
    {
        int n=g.size();
        memset(tin,0,sizeof(tin));
        memset(tout,0,sizeof(tout));
        timer=0;
        for(int i=0;i<n;++i)
        {
            if(!tin[i])
                DFS(i,i);
        }
    }
    void DFS(int node,int parent){
        tin[node]=++timer;
        up[node][0]=parent;
        int i;
        for(i=1;i<=len;i++){
            up[node][i]=up[up[node][i-1]][i-1];
        }
        for(auto e:g[node]){
            if(e!=parent)DFS(e,node);
        }
        tout[node]=++timer;
        return;
    }
    bool is_ancestor(int u,int v){//if u is an ancestor of v
        return tin[u]<=tin[v]&&tout[u]>=tout[v];
    }
    int lca(int u,int v){
        if(is_ancestor(u,v))return u;
        if(is_ancestor(v,u))return v;
        for(int i=len;i>=0;i--){
            if(!is_ancestor(up[u][i],v))u=up[u][i];
        }
        return up[u][0];
    }
}
