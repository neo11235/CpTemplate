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
#define infl 0x7ffffffffffffff
#define infi  0x7fffffff
#define fill_(a,b) fill(a.begin(),a.end(),b)
#define pb push_back
#define xx first
#define yy second
struct dsu_save{
    int u,rnku,v,rnkv;
    dsu_save(){}
    dsu_save(int _u,int _rnku,int _v,int _rnkv):u(_u),rnku(_rnku),v(_v),rnkv(_rnkv){}
};
struct dsu_with_rollbacks{
    vector<int> p,rnk;
    int ncomp;
    stack<dsu_save> op;
    dsu_with_rollbacks(){}
    dsu_with_rollbacks(int n){
        p.resize(n);
        rnk.resize(n);
        for(int i=0;i<n;i++){
            p[i]=i;
            rnk[i]=0;
        }
        ncomp=n;
    }
    int find_set(int v){
        while(v!=p[v])
            v=p[v];
        return v;
    }
    bool unite(int u,int v){
        u=find_set(u);
        v=find_set(v);
        if(u==v)
            return false;
        ncomp--;
        if(rnk[u]>rnk[v])swap(u,v);
        op.push(dsu_save(u,rnk[u],v,rnk[v]));
        p[u]=v;
        if(rnk[u]==rnk[v])
            rnk[v]++;
        return true;
    }
    void rollback(void){
        if(op.empty())return;
        dsu_save x=op.top();
        op.pop();
        ncomp++;
        p[x.u]=x.u;
        rnk[x.u]=x.rnku;
        p[x.v]=x.v;
        rnk[x.v]=x.rnkv;
    }
    void reset(void){
        while(!op.empty()){
            rollback();
        }
    }
};
struct query{
    int u;
    int v;
    bool united;
    query(){}
    query(int _u,int _v):u(_u),v(_v){}
};
vector<query> Q(200000);
#define block_size 500
struct range{
    int l;
    int r;
    int idx;
    range(){}
    bool operator<(range other)const{
        return mp(l/block_size,r)<mp(other.l/block_size,r);
    }
};
int main(){

    int t,n,m,q,u,v,i;
    for(i=0;i<200000;i++){
        Q[i].united=false;
    }
    sci(t);
    while(t--){
        sci(n,m,q);
        for(i=0;i<m;i++){
            sci(Q[i].u,Q[i].v);
            Q[i].u--;
            Q[i].v--;
        }
        vector<range> R(q);
        vector<int> sol(q);
        dsu_with_rollbacks dsu(n);
        for(i=0;i<q;i++){
            sci(R[i].l,R[i].r);
            R[i].l--;
            R[i].r--;
            R[i].idx=i;
        }
        sort(R.begin(),R.end());
        int cur_l=0,cur_r=-1,cur_b=block_size-1;
        for(i=0;i<q;i++){
           if(cur_b<R[i].l){
                dsu.reset();
                while(cur_b<R[i].l)
                    cur_b+=block_size;
                cur_l=cur_b+1;
                cur_r=cur_b;
           }
           if(R[i].r<=cur_b){
                dsu.reset();
                for(int j=R[i].l;j<=R[i].r;j++){
                    dsu.unite(Q[j].u,Q[j].v);
                }
                sol[R[i].idx]=dsu.ncomp;
                dsu.reset();
                continue;
           }
           while(cur_r<R[i].r){
                cur_r++;
                Q[cur_r].united=dsu.unite(Q[cur_r].u,Q[cur_r].v);
           }
           while(cur_r>R[i].r){
                if(Q[cur_r].united)
                    dsu.rollback();
                Q[cur_r].united=false;
                cur_r--;
           }
           while(cur_l>R[i].l){
                cur_l--;
                Q[cur_l].united=dsu.unite(Q[cur_l].u,Q[cur_l].v);
           }
           sol[R[i].idx]=dsu.ncomp;
           while(cur_l<=cur_b){
                if(Q[cur_l].united)
                    dsu.rollback();
                Q[cur_l].united=false;
                cur_l++;
           }
        }
        for(auto e:sol){
            printf("%d\n",e);
        }
    }
    return 0;
}
