#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#define infi 0x7fffffff
void dijkstra(vector<vector<pii > >&G,int s,vector<int>& ans,vector<int>& parent){
    int n=G.size();
    ans.assign(n,infi);
    parent.assign(n,-1);
    priority_queue<pii,vector<pii>,greater<pii> > pq;
    ans[s]=0;
    pq.push(mp(0,s));
    int v,d_v,to,len;
    while(!pq.empty()){
        v=pq.top().second;
        d_v=pq.top().first;
        pq.pop();
        if(d_v!=ans[v])continue;

        for(auto edge:G[v]){//<vertex,weight> pair
            to=edge.first;
            len=edge.second;
            if(ans[v]+len<ans[to]){
                ans[to]=ans[v]+len;
                parent[to]=v;
                pq.push(mp(ans[to],to));
            }
        }
    }
    return;
}
/*imp2*/
vector<vector<pii>> G;
vector<int> sp1;
vector<int> sp2;
void dijkstra(int n,int s){
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    pq.push(mp(s,0));
    pii tmp;
    while(!pq.empty()){
        tmp=pq.top();
        pq.pop();
        if(sp1[tmp.first]==tmp.second||sp2[tmp.first]==tmp.second)continue;
        if(tmp.second<sp1[tmp.first]){
            sp2[tmp.first]=sp1[tmp.first];
            sp1[tmp.first]=tmp.second;
            for(auto E:G[tmp.first]){
                pq.push(mp(E.first,E.second+sp1[tmp.first]));
                if(sp2[tmp.first]!=infi)
                    pq.push(mp(E.first,E.second+sp2[tmp.first]));
            }
        }
        else{
            if(tmp.second<sp2[tmp.first]){
                sp2[tmp.first]=tmp.second;
                for(auto E:G[tmp.first]){
                    pq.push(mp(E.first,E.second+sp2[tmp.first]));
                }
            }
        }
    }
}
/*********************finding articulation point************/
vector<vector<int> > G;
vector<int> vis;
vector<int> low;
vector<int> dis;
vector<int> is_art;
int timer;
void art_dfs(int node,int p){
    vis[node]=1;
    dis[node]=low[node]=++timer;
    int child=0;
    for(int i:G[node]){
        if(i==p)continue;
        if(vis[i]){
            low[node]=min(low[node],dis[i]);
        }
        else{
            child++;
            art_dfs(i,node);
            low[node]=min(low[node],low[i]);
            if(dis[node]<=low[i]&&p!=-1){
                is_art[node]=1;
            }
        }
    }
    if(p==-1&&child>1)is_art[node]=1;
    ++timer;
}
/**********************/
/*********************finding bridge************/
vector<vector<int> > G;
vector<int> vis;
vector<int> low;
vector<int> dis;
vector<pii >bridges;
int timer;
void B_dfs(int node,int p=-1){
    vis[node]=1;
    dis[node]=low[node]=++timer;
    for(int i:G[node]){
        if(i==p)continue;
        if(vis[i]){
            low[node]=min(low[node],dis[i]);
        }
        else{
            B_dfs(i,node);
            low[node]=min(low[node],low[i]);
            if(dis[node]<low[i]){
                bridges.push_back(mp(node,i));
            }
        }
    }
    ++timer;
}
/**********************/
/**********belman ford//not completely debugged************/
vector<vector<pair<int,int> > > G;

int bell_ford(vector<int>&ans,int source){
    fill(begin(ans),end(ans),inf);
    ans[source]=0;
    int i,j,k;
    bool chk;
    for(i=0;i<G.size()+2;i++){
        chk=false;
        for(j=0;j<G.size();j++){
            if(ans[j]==inf)continue;
            for(k=0;k<G[j].size();k++){

                if(ans[G[j][k].first]>ans[j]+G[j][k].second){
                    chk=true;
                    ans[G[j][k].first]=ans[j]+G[j][k].second;
                }
            }
        }
        if(!chk)break;
    }
    //if(i==(G.size()+2))return -1;
    return 0;
}
/**************************************************/

/*******************************union find*****************/
class DSU{
public:
    int* parent;
    int* rank_;
    int size_;
    DSU(){
        size_=0;
    }
    DSU(int sz){
        size_=sz;
        rank_=new int[sz];
        memset(rank_,0,sizeof(int)*sz);
        parent=new int[sz];
        for(int i=0;i<sz;i++)parent[i]=i;
    }
    void resize(int sz){
        if(size_!=0){
            delete[] parent;
            delete[] rank_;
        }
        size_=sz;
        rank_=new int[sz];
        memset(rank_,0,sizeof(int)*sz);
        parent=new int[sz];
        for(int i=0;i<sz;i++)parent[i]=i;
    }
    void unify(int ld1,int ld2){//must pass leader of a set
        if(rank_[ld1]<rank_[ld2]){
            parent[ld1]=ld2;
        }
        else if(rank_[ld2]<rank_[ld1]){
            parent[ld2]=ld1;
        }
        else{
            parent[ld2]=ld1;
            rank_[ld1]++;
        }
    }
    int find_set(int v){
        int tv=v,t;
        while(v!=parent[v])
            v=parent[v];
        while(tv!=v){
            t=parent[tv];
            parent[tv]=v;
            tv=t;
        }
        return v;
    }
    void unify2(int v1,int v2){//v1 v2 are not necessarily leader
        unify(find_set(v1),find_set(v2));
    }
};
/***************tarjans offline algorithm for lca**************/
vector<vector<int> >T;//a tree//otherwise dfs tree will be used
vector<vector<int> >query;
vector<int> vis;
vector<int> ancestor;
vector<int> ans;//to the query//must be resized same as query
vector<vector<int> >qid;
DSU tar_dsu;

void tarjans_dfs(int node){
    vis[node]=1;
    ancestor[node]=node;
    for(auto e:T[node]){
        if(!vis[e]){
            tarjans_dfs(e);
            tar_dsu.unify2(node,e);
            ancestor[tar_dsu.find_set(node)]=node;
        }
    }
    for(int i=0;i<(int)query[node].size();i++){
        if(vis[query[node][i]]){
            ans[qid[node][i]]=ancestor[tar_dsu.find_set(query[node][i])];
        }
    }
}

void init_and_TI(int n,int m){//m query will be taken//n size of the tree
    int i,u,v;
    query.assign(n,vector<int>());
    qid.assign(n,vector<int>());
    ans.resize(m);
    for(i=0;i<m;i++){
        sci(u,v);
        if(u==v){
            ans[i]=u-1;
            continue;
        }
        u--;v--;//might not use;

        query[u].push_back(v);
        query[v].push_back(u);
        qid[u].push_back(i);
        qid[v].push_back(i);
    }
    vis.assign(n,0);
    ancestor.resize(n);
    tar_dsu.resize(n);
    tarjans_dfs(0);
    return;
}
/********************************************/
#endif // GRAPH_H_INCLUDED
