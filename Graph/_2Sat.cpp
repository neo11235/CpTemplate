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

Graph G;
vi vis;
vi dis;
vi low;
vi cstack;
stack<int> sstack;
int curTime=0;
int sccCount=1;
vi sccId;
vi _2sat;
bool tarjansDfs(int node)
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
        if(!tarjansDfs(e))
            return false;
        low[node]=min(low[node],low[e]);
    }
    if(low[node]==dis[node])
    {
        int n=(int)G.size()/2;
        while(sstack.top()!=node)
        {
            int u=sstack.top();
            sccId[u]=sccCount;
            cstack[u]=0;

            if(sccId[(u+n)%(2*n)]==-1){
                if(u<n)
                {
                    _2sat[u]=1;
                }
                else{
                    _2sat[u-n]=0;
                }
            }
            else if(sccId[(u+n)%(2*n)]==sccCount)
            {
                return false;
            }
            sstack.pop();
        }
        int u=sstack.top();
        sccId[u]=sccCount;
        cstack[u]=0;

        if(sccId[(u+n)%(2*n)]==-1){
            if(u<n)
            {
                _2sat[u]=1;
            }
            else{
                _2sat[u-n]=0;
            }
        }
        else if(sccId[(u+n)%(2*n)]==sccCount)
        {
            return false;
        }
        sstack.pop();
        ++sccCount;
    }
    return true;
}
void addEdge(int u,int v,int n)
{
    G[(u+n)%(2*n)].push_back(v);
    G[(v+n)%(2*n)].push_back(u);
}
int main(){
    int n,m;
    sci(m,n);
    G.resize(2*n);
    vis.assign(2*n,0);
    dis.resize(2*n);
    low.resize(2*n);
    cstack.resize(2*n);
    sccId.assign(2*n,-1);
    _2sat.resize(n);

    int i;
    char a[2],b[2];
    int u,v;
    for(i=0;i<m;i++)
    {
        scanf("%s %d %s %d",a,&u,b,&v);
        u--;
        v--;
        if(a[0]=='-')
            u+=n;
        if(b[0]=='-')
            v+=n;
        addEdge(u,v,n);
    }
    bool exist=true;
    for(i=0;i<2*n;i++)
    {
        if(!vis[i])
        {
            if(!tarjansDfs(i)){
                exist=false;
                break;
            }
        }
    }
    if(exist)
    {
        for(auto e:_2sat)
        {
            if(e)
                cout<<"+ ";
            else
                cout<<"- ";
        }
        cout<<endl;
    }
    else{
        cout<<"IMPOSSIBLE"<<endl;
    }

}
