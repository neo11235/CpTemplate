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

#define read freopen("outofplace.in","r",stdin)
#define write freopen("outofplace.out","w",stdout)
#define infl 0xfffffffffffffffll
#define infi  0x1fffffff
#define mp(a,b) make_pair(a,b)

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define bound(i,j,n,m) ((i)<n&&(j)<m&&(i)>=0&&(j)>=0)
const ll mod=1000000007ll;


template<class T>
class segTree// point update range query
{
public:
    T* sgt;
    int n;
    T (*combine)(T,T);
    segTree(T (*combine)(T,T),int sz)
    {
        n=sz;
        sgt=new T[4*sz];
        memset(sgt,0,sizeof(T)*4*sz);
        this->combine=combine;
    }
    segTree(T (*combine)(T,T),T* data,int sz)
    {
        n=sz;
        sgt=new T[4*sz];
        this->combine=combine;
        build(data,1,0,n-1);
    }

    void build(T* data,int v,int vl,int vr)
    {
        if(vl==vr)
        {
            sgt[v]=data[vl];
            return;
        }
        int mid=(vl+vr)/2;
        build(data,2*v,vl,mid);
        build(data,2*v+1,mid+1,vr);
        sgt[v]=combine(sgt[2*v],sgt[2*v+1]);
    }
    void update(int v,int vl,int vr,int pos,T el)
    {
        if(vl==vr)
        {
            sgt[v]=el;
            return;
        }
        int mid=(vl+vr)/2;
        if(pos<=mid)
            update(2*v,vl,mid,pos,el);
        else
            update(2*v+1,mid+1,vr,pos,el);
        sgt[v]=combine(sgt[2*v],sgt[2*v+1]);
    }
    void update(int pos,T el)
    {
        update(1,0,n-1,pos,el);
    }
    T query(int v,int vl,int vr,int l,int r)
    {
        if(vl==l&&vr==r)
            return sgt[v];
        int mid=(vl+vr)/2;
        if(r<=mid)
            return query(2*v,vl,mid,l,r);
        else if(l>mid)
            return query(2*v+1,mid+1,vr,l,r);
        else
            return combine(query(2*v,vl,mid,l,mid),query(2*v+1,mid+1,vr,mid+1,r));
    }
    T query(int l,int r)
    {
        return query(1,0,n-1,l,r);
    }
};
ll combine(ll a,ll b)
{
    return (a+b)%mod;
}

ll numberOfIS(int* data,int sz)//take mod
{
    const int mxrange=200000;
    segTree<ll> sgt(combine,mxrange+1);
    ll ans=0,tmp;
    for(int i=sz-1;i>=0;i--)
    {
        tmp=sgt.query(data[i]+1 ,mxrange)+1;
        ans=(ans+tmp)%mod;
        sgt.update(data[i],(tmp+sgt.query(data[i],data[i]))%mod);
    }
    return ans;
}
class BIT{//1 based indexing
public:
    ll* A=NULL;
    int range;
    BIT(int range)
    {
        A=new ll[range+1];
        memset(A,0,sizeof(ll)*(range+1));
        this->range=range;
    }
    ll sum(int i)
    {
        ll s=0;
        while(i>0)
        {
            s+=A[i];
            s%=mod;
            i-=LSB(i);
        }
        return s;
    }
    void add(int i,ll k)
    {
        while(i<=range)
        {
            A[i]+=k;
            A[i]%=mod;
            i+=LSB(i);
        }
    }
    ~BIT()
    {
        if(A!=NULL)
            delete[] A;
    }
};

ll numberOfISBIT(int* data,int sz)//take mod
{
    const int mxrange=200000;
    BIT bit(mxrange);
    memset(bit.A,0,sizeof(ll)*(mxrange+1));
    ll ans=0,tmp;
    for(int i=sz-1;i>=0;i--)
    {
        tmp=(bit.sum(mxrange)-bit.sum(data[i])+1+mod)%mod;
        ans=(ans+tmp)%mod;
        bit.add(data[i],tmp);
    }
    return ans;
}
const ll mod=1000000007ll;
class BIT{//1 based indexing
public:
    ll* A=NULL;
    int range;
    BIT(){}
    BIT(int range)
    {
        A=new ll[range+1];
        memset(A,0,sizeof(ll)*(range+1));
        this->range=range;
    }
    void resize(int range)
    {
        A=new ll[range+1];
        memset(A,0,sizeof(ll)*(range+1));
        this->range=range;
    }
    ll sum(int i)
    {
        ll s=0;
        while(i>0)
        {
            s+=A[i];
            i-=LSB(i);
        }
        return s%mod;
    }
    void add(int i,ll k)
    {
        while(i<=range)
        {
            A[i]+=k;
            if(A[i]>=mod)
                A[i]-=mod;
            i+=LSB(i);
        }
    }
    void clear()
    {
        memset(A,0,sizeof(ll)*(range+1));
    }
    ~BIT()
    {
        if(A!=NULL)
            delete[] A;
    }
};
int mxrange=100000;
BIT bit;
/*ll numberOfISBIT(int* data,int sz)//take mod
{

    ll ans=0,tmp;
    for(int i=sz-1;i>=0;i--)
    {
        tmp=(bit.sum(mxrange)-bit.sum(data[i])+1+mod);
        if(tmp>=mod)
            tmp-=mod;
        ans=(ans+tmp);
        if(ans>=mod)
            ans-=mod;
        bit.add(data[i],tmp);
    }
    for(int i=0;i<sz;i++)
    {
        tmp=(-bit.sum(data[i])+bit.sum(data[i]-1)+mod);
        if(tmp>=mod)
            tmp-=mod;
        bit.add(data[i],tmp);
    }
    return ans;
}*/
int d[1000001];
int numberOfISBIT(int* sequence,int sz)
{
    int i;
    for(i=0;i<sz;i++)
    {
        d[i]=bit.sum(sequence[i]-1);
        d[i]++;
        if(d[i]>mod)
            d[i]-=mod;
        bit.add(sequence[i],d[i]);
    }
    int ans=0;
    for(i=0;i<sz;i++)
    {
        ans+=d[i];
        if(ans>=mod)
            ans-=mod;
        bit.add(sequence[i],mod-d[i]);
    }
    return ans;
}
