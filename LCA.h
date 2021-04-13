#ifndef LCA_H_INCLUDED
#define LCA_H_INCLUDED
vector<vector<int> > up;
vector<vector<int> > min_;
vector<vector<int> > max_;
vector<int> tin,tout;
int len;
int timer;
vector<vector<pii > > G;

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
    int rval=inf;
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
    int rval=0;
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


#endif // LCA_H_INCLUDED
