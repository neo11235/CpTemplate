class DSU{
public:
    int* parent;
    int* rank_;
    int sz;
    int ntree;
    DSU(){sz=0;}
    DSU(int n){
        parent=new int[n];
        rank_=new int[n];
        sz=ntree=n;
        for(int i=0;i<n;i++){
            parent[i]=i;
            rank_[i]=0;
        }
    }
    void resize(int n){
        parent=new int[n];
        rank_=new int[n];
        sz=ntree=n;
        for(int i=0;i<n;i++){
            parent[i]=i;
            rank_[i]=0;
        }
    }
    int findSet(int i){
        return i==parent[i]?i:(parent[i]=findSet(parent[i]));
    }

    bool isSameSet(int i,int j){
        return findSet(i)==findSet(j);
    }
    void unionSet(int i,int j){
        int pi=findSet(i);
        int pj=findSet(j);
        if(pi!=pj){
            if(rank_[pi]>rank_[pj])
                parent[pj]=pi;
            else{
                parent[pi]=pj;
                if(rank_[pi]==rank_[pj])
                    rank_[pj]++;
            }
            ntree--;
        }
    }
    ~DSU(){
        if(sz>0){
            delete[] parent;
            delete[] rank_;
        }
    }
};


vector<pair<int,pii> > edge;
DSU dsu;
ll kruskal(int n){
    dsu.resize(n);
    sort(edge.begin(),edge.end());
    ll ans=0;
    for(auto e:edge){
        if(dsu.isSameSet(e.second.first,e.second.second))
            continue;
        ans+=e.first;
        dsu.unionSet(e.second.first,e.second.second);
    }
    return ans;
}
/*************************************/
class DSU{
public:
    int* parent;
    int* rank_;
    int* pop;
    int sz;
    int ntree;
    int mxpop;
    DSU(){sz=0;}
    DSU(int n){
        parent=new int[n];
        rank_=new int[n];
        pop=new int[n];
        memset(rank_,0,sizeof(int)*n);
        sz=ntree=n;
        for(int i=0;i<n;i++){
            parent[i]=i;
            pop[i]=1;
        }
        mxpop=0;
    }
    void resize(int n){
        parent=new int[n];
        rank_=new int[n];
        pop=new int[n];
        memset(rank_,0,sizeof(int)*n);
        sz=ntree=n;
        for(int i=0;i<n;i++){
            parent[i]=i;
            pop[i]=1;
        }
        mxpop=0;
    }
    int findSet(int i){
        return i==parent[i]?i:(parent[i]=findSet(parent[i]));
    }

    bool isSameSet(int i,int j){
        return findSet(i)==findSet(j);
    }
    void unionSet(int i,int j){
        int pi=findSet(i);
        int pj=findSet(j);
        if(pi!=pj){
            if(rank_[pi]>rank_[pj]){
                parent[pj]=pi;
                pop[pi]+=pop[pj];
                mxpop=max(mxpop,pop[pi]);
            }
            else{
                parent[pi]=pj;
                pop[pj]+=pop[pi];
                mxpop=max(mxpop,pop[pj]);
                if(rank_[pi]==rank_[pj])
                    rank_[pj]++;
            }
            ntree--;
        }
    }
    ~DSU(){
        if(sz>0){
            delete[] parent;
            delete[] rank_;
            delete[] pop;
        }
    }
};

/*************quick implementation*****************/
#define MAX_SIZE 1000000
int p[MAX_SIZE];
int rnk[MAX_SIZE];
int findSet(int v)
{
    return p[v]=(p[v]==v?v:findSet(p[v]));
}
void unionSet(int u,int v)
{
    u=findSet(u);
    v=findSet(v);
    if(u==v)
        return;
    if(rnk[u]==rnk[v])
    {
        rnk[u]++;
    }
    if(rnk[u]<rnk[v])
    {
        p[u]=v;
    }
    else
    {
        p[v]=u;
    }
}
/************************************************/
/*************DSU to support parity of path************/
struct DSU
{
    int* leader;
    int* rnk;
    int* par;
    vector<bool> isBipartite;//implement later,check if connected component of a leader is  bipartite or not
    int n;
    int ncomponent;
    DSU()
    {
        n=0;
    }
    void initialize()
    {
        for(int i=0;i<n;i++)
        {
            leader[i]=i;
        }
        memset(rnk,0,sizeof(int)*n);
        memset(par,0,sizeof(int)*n);
    }
    DSU(int length)
    {
        leader=new int[length];
        rnk=new int[length];
        par=new int[length];
        n=ncomponent=length;
        initialize();
    }
    void resize(int length)
    {
        if(n!=0)
        {
            delete[] leader;
            delete[] rnk;
            delete[] par;
        }
        leader=new int[length];
        rnk=new int[length];
        par=new int[length];
        n=ncomponent=length;
        initialize();
    }
    pair<int,int> findSet(int i)//returns <head,parity> //path compression
    {
        if(leader[i]==i)
            return mp(i,0);
        int parity=par[i];
        pair<int,int> res=findSet(leader[i]);
        res.second^=parity;
        par[i]=res.second;
        leader[i]=res.first;
        return res;
    }
    void unionSet(int u,int v)
    {
        pair<int,int> uu,vv;
        uu=findSet(u);
        vv=findSet(v);
        if(uu.first==vv.first)
            return;
        if(rnk[uu.first]>rnk[vv.first])
            swap(uu,vv);
        if(rnk[uu.first]==rnk[vv.first])
            rnk[vv.first]++;
        leader[uu.first]=vv.first;
        par[uu.first]=1^uu.second^vv.second;
    }
};
