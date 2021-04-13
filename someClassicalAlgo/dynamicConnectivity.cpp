/******solution to the https://codeforces.com/edu/course/2/lesson/7/3/practice/contest/289392/problem/C**********/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vi vector<int>
#define triple pair<pair<int,int>,int>
#define vpii vector<pii >
#define Graph vector<vector<int> >
#define WGraph vector<vector<pii>>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define xx first
#define yy second

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
#define infi  2000000000
#define LSB(i) ((i)&(-(i)))
#define mp(a,b) make_pair(a,b)

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);

#define bound(i,j,n,m) ((i)<n&&(j)<m&&(i)>=0&&(j)>=0)

inline void debugMode()
{
    #ifndef ONLINE_JUDGE
    read;
    //write;
    #endif // ONLINE_JUDGE
}
class PersistentDsu{
public:
    struct DsuSave{
        int u,rnku,v,rnkv;
        DsuSave(){}
        DsuSave(int u,int rnku,int v,int rnkv):u(u),rnku(rnku),v(v),rnkv(rnkv){}
    };
    stack<DsuSave> op;
    int* p,*rnk,ntree,n;
    PersistentDsu()
    {
        n=0;
    }
    void initialize()
    {
        for(int i=0;i<n;i++)
            p[i]=i;
        memset(rnk,0,sizeof(int)*n);
    }
    PersistentDsu(int n)
    {
        this->n=n;
        p=new int[n];
        rnk=new int[n];
        ntree=n;
        initialize();
    }
    void resize(int nn)
    {
        if(n)
        {
            delete[] p;
            delete[] rnk;
        }
        p=new int[nn];
        rnk=new int[nn];
        ntree=nn;
        n=nn;
        initialize();
        while(!op.empty())
        {
            op.pop();
        }
    }
    int findSet(int i)
    {
        while(i!=p[i])
        {
            i=p[i];
        }
        return i;
    }
    bool unionSet(int u,int v)//keep track of which union operation actually changed the sets
    {
        u=findSet(u);
        v=findSet(v);
        if(u==v)
            return false;
        if(rnk[u]>rnk[v])
            swap(u,v);
        op.push(DsuSave(u,rnk[u],v,rnk[v]));
        if(rnk[u]==rnk[v])
        {
            rnk[v]++;
        }
        p[u]=v;
        ntree--;
        return true;
    }
    bool rollback()//rollback last operation;
    {
        if(op.empty())
            return false;
        DsuSave pstate=op.top();
        op.pop();
        p[pstate.u]=pstate.u;
        rnk[pstate.v]=pstate.rnkv;
        ntree++;
        return true;
    }
};
struct query{
    int l,r,u,v,indx;
    query(){}
    query(int l,int r,int u,int v,int indx):l(l),r(r),u(u),v(v),indx(indx){}
};
vi ans;
PersistentDsu dsu;
void solve(int l,int r,const vector<query>& queries)
{
    if(l>r)
        return;
    if(l==r)
    {
        int rl=0;
        for(query q:queries)
        {
            if(q.l<=l&&q.r>r)
            {
                rl+=dsu.unionSet(q.u,q.v);
            }
        }
        for(query q:queries)
        {
            if(q.r==-1&&q.l==l)
            {
                ans[q.indx]=dsu.ntree;
            }
        }
        while(rl)
        {
            dsu.rollback();
            rl--;
        }
        return;
    }
    int rl=0;
    vector<query> qs2;
    for(query q:queries)
    {
        if(q.r==-1)
        {
            if(q.l<=r&&q.l>=l)
                qs2.push_back(q);
        }
        else if(q.l<=l&&q.r>=r)
        {
            rl+=dsu.unionSet(q.u,q.v);
        }
        else if((q.l>=l&&q.r<=r)||(q.l<=r&&q.r>=l)||(q.l<=r&&q.r>=r))
            qs2.push_back(q);
    }
    int mid=(l+r)/2;
    solve(l,mid,qs2);
    solve(mid+1,r,qs2);
    while(rl)
    {
        dsu.rollback();
        rl--;
    }
    return;
}
void solvecases(int cse)
{
    int n,m;
    cin>>n>>m;
    dsu.resize(n);
    map<pii,int> tmap;
    vector<query> qs;
    int indx=0;
    for(int i=0;i<m;i++)
    {
        string s;
        int u,v;
        cin>>s;
        if(s[0]=='?')
        {
            qs.push_back(query(i+1,-1,-1,-1,indx++));
        }
        else if(s[0]=='+')
        {
            cin>>u>>v;
            u--;
            v--;
            if(u>v)
                swap(u,v);
            tmap[mp(u,v)]=i+1;
        }
        else
        {
            cin>>u>>v;
            u--;
            v--;
            if(u>v)
                swap(u,v);
            int tl=tmap[mp(u,v)];
            qs.push_back(query(tl,i+1,u,v,-1));
            tmap[mp(u,v)]=0;
        }
    }
    for(auto e:tmap)
    {
        if(!e.second)
            continue;
        qs.push_back(query(e.second,INT_MAX,e.first.first,e.first.second,-1));
    }
    ans.resize(indx);
    solve(1,m,qs);
    for(int i:ans)
        cout<<i<<'\n';
}
