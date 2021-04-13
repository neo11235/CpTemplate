/**********************************/
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
    void reset()
    {
        if(sz==0)
            return;
        ntree=sz;
        for(int i=0;i<sz;i++)
        {
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
