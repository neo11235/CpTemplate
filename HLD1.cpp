#include <bits/stdc++.h>
using namespace std;
#define sci1(a) scanf("%d",&a)
#define sci2(a,b) scanf("%d %d",&a,&b)
#define sci3(a,b,c) scanf("%d %d %d",&a,&b,&c)
#define scs(s) scanf("%s",s)
#ifndef GET_MACRO

#define GET_MACRO(__1,__2,__3,NAME,...) NAME

#endif // GET_MACRO

#define sci(...) GET_MACRO(__VA_ARGS__,sci3,sci2,sci1)(__VA_ARGS__)
#define ll long long
#define pii pair<int,int>
#define mp(a,b) make_pair(a,b)
#define LSB(i) ((i)&(-i))
#define read freopen("input.txt","r",stdin)
#define write freopen("output.txt","w",stdout)
vector<vector<int> >G;
vector<int> parent,depth,heavy,head,pos;
vector<int> node_val;
vector<int> sgt;
int cur_pos;
void sgt_build(int v,int vl,int vr){
    if(vl==vr){
        sgt[v]=node_val[vl];
        return;
    }
    int mid=(vl+vr)/2;
    sgt_build(2*v,vl,mid);
    sgt_build(2*v+1,mid+1,vr);
    sgt[v]=sgt[2*v]+sgt[2*v+1];
    return;
}
void sgt_update(int v,int vl,int vr,int np,int nval){
    if(vl==vr){
        sgt[v]=nval;
        return;
    }
    int mid=(vl+vr)/2;
    if(np<=mid)
        sgt_update(2*v,vl,mid,np,nval);
    else
        sgt_update(2*v+1,mid+1,vr,np,nval);
    sgt[v]=sgt[2*v]+sgt[2*v+1];
}
int sgt_query(int v,int vl,int vr,int l,int r){
    if(vl==l&&vr==r){
        return sgt[v];
    }
    int mid=(vl+vr)/2;
    if(r<=mid)
        return sgt_query(2*v,vl,mid,l,r);
    else if(l>mid)
        return sgt_query(2*v+1,mid+1,vr,l,r);
    else
        return sgt_query(2*v,vl,mid,l,mid)+sgt_query(2*v+1,mid+1,vr,mid+1,r);
}
int dfs(int node){
    int sz=1;
    int max_c_size=0;
    for(auto c:G[node]){
        if(c!=parent[node]){
            parent[c]=node;
            depth[c]=depth[node]+1;
            int c_size=dfs(c);
            sz+=c_size;
            if(c_size>max_c_size){
                max_c_size=c_size;
                heavy[node]=c;
            }
        }
    }
    return sz;
}
void decompose(int node,int h){
    pos[node]=cur_pos++;
    head[node]=h;
    if(heavy[node]!=-1)
        decompose(heavy[node],h);
    for(int c:G[node]){
        if(c!=parent[node]&&c!=heavy[node])
            decompose(c,c);
    }
    return;
}
int query(int a,int b,int n){//n number of node in the tree
    int res=0;
    while(head[a]!=head[b]){
        if(depth[head[a]]>depth[head[b]])swap(a,b);
        res=res+sgt_query(1,0,n-1,pos[head[b]],pos[b]);
        b=parent[head[b]];
    }
    if(depth[a]>depth[b])swap(a,b);
    res=res+sgt_query(1,0,n-1,pos[a],pos[b]);
    return res;
}
void init(int n){
    parent.resize(n);
    depth.resize(n);
    heavy.assign(n,-1);
    head.resize(n);
    pos.resize(n);

    parent[0]=0;//might change later
    dfs(0);
    cur_pos=0;
    decompose(0,0);
}
int main(){
    int t,cse,u,v,i,j,n,q,id;
    int data[30000];
    sgt.resize(4*30000);
    sci(t);
    for(cse=0;cse<t;cse++){
        sci(n);
        G.assign(n,vector<int>());
        for(i=0;i<n;i++)sci(data[i]);
        for(i=1;i<n;i++){
            sci(u,v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        init(n);
        node_val.resize(n);
        for(i=0;i<n;i++){
            node_val[pos[i]]=data[i];
        }
        sgt_build(1,0,n-1);

        sci(q);
        printf("Case %d:\n",cse+1);
        for(i=0;i<q;i++){
            sci(id,u,v);
            if(id){
                sgt_update(1,0,n-1,pos[u],v);
            }
            else{
                printf("%d\n",query(u,v,n));
            }
        }
    }
    return 0;
}
