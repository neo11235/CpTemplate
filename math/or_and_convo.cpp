///or convolution
template<class T>
void orTransform(vector<T>& a,bool invert=false)
{
    int n=a.size();
    assert(!(n&(n-1)));
    for(int len=2;len<=n;len=len<<1)
    {
        for(int i=0;i<n;i+=len)
        {
            int l2=len>>1;
            for(int j=i;j<i+l2;++j){
                if(invert)
                {
                    T tmp=a[j+l2];
                    a[j+l2]=(a[j]-a[j+l2]);
                    a[j]=tmp;
                }
                else
                {
                    T tmp=a[j];
                    a[j]+=a[j+l2];
                    a[j+l2]=tmp;
                }
            }
        }
    }
}
template<class T>
vector<T> multiply(vector<T> a,vector<T> b)
{
    int n=a.size();
    assert(n==b.size()&&(!(n&(n-1))));
    orTransform(a);
    orTransform(b);
    for(int i=0;i<n;++i)
    {
        a[i]*=b[i];

    }
    orTransform(a,true);
    return a;
}

///with mod
const ll mod=998244353;
template<class T>
void orTransform(vector<T>& a,bool invert=false)
{
    int n=a.size();
    assert(!(n&(n-1)));
    for(int len=2;len<=n;len=len<<1)
    {
        for(int i=0;i<n;i+=len)
        {
            int l2=len>>1;
            for(int j=i;j<i+l2;++j){
                if(invert)
                {
                    T tmp=a[j+l2];
                    a[j+l2]=(a[j]-a[j+l2]+mod)%mod;
                    a[j]=tmp;
                }
                else
                {
                    T tmp=a[j];
                    a[j]+=a[j+l2];
                    a[j]%=mod;
                    a[j+l2]=tmp;
                }
            }
        }
    }
}
template<class T>
vector<T> multiply(vector<T> a,vector<T> b)
{
    int n=a.size();
    assert(n==b.size()&&(!(n&(n-1))));
    orTransform(a);
    orTransform(b);
    for(int i=0;i<n;++i)
    {
        a[i]*=b[i];
        a[i]%=mod;

    }
    orTransform(a,true);
    for(auto &e:a){
        e%=mod;
        e=(e+mod)%mod;
    }
    return a;
}

///and convolution using or convolution
template<class T>
vector<T> multiplyAnd(vector<T> a,vector<T> b)
{
    int n=a.size();
    assert(n==b.size()&&(!(n&(n-1))));
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    vector<T> out=multiply(a,b);
    reverse(out.begin(),out.end());
    return out;
}

//to be implemented
//zeta and mobius transform
//normal implementation found on the net
void zeta(vll & d,int m)
{
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<(1<<m);++j)
        {
            if(j&(1<<i))
                d[j]+=d[j^(1<<i)];
        }
    }
}
void zinv(vll &d,int m)
{
    for(int i=0;i<(1<<m);++i)
    {
        d[i]=((__builtin_popcount(i)%2?-1:1)*d[i]);
    }
    zeta(d,m);
    for(int i=0;i<(1<<m);++i)
    {
        d[i]=((__builtin_popcount(i)%2?-1:1)*d[i]);
    }
}

//faster version
//zeta is about 1.5 times faster than previous version
//zinv is about 1.8 times faster than previous version
//these 2 might be implemented very fast in a gpu
//zeta transform or sos dp
void zeta(vll& d,int m)
{
    int n=1<<m;
    for(int len=2;len<=n;len*=2)
    {
        for(int i=0;i<n;i+=len)
        {
            int l2=len>>1;
            for(int j=i;j<i+l2;++j)
            {
                d[j+l2]+=d[j];
            }
        }
    }
}
//zeta_inverse or mobius transform
void zinv(vll &d,int m)
{
    int n=1<<m;
    for(int len=2;len<=n;len*=2)
    {
        for(int i=0;i<n;i+=len)
        {
            int l2=len>>1;
            for(int j=i;j<i+l2;++j)
            {
                d[j+l2]-=d[j];
            }
        }
    }
}

//subset sum convolution
//not fully tested,got some error if used with mod
#define MAX_SIZE 1<<20
ll f[MAX_SIZE];
ll g[MAX_SIZE];
ll res[MAX_SIZE];
ll fhat[20][MAX_SIZE];
ll ghat[20][MAX_SIZE];
ll h[20][MAX_SIZE];
void subsetConvolution(int m)
{
    int n=1<<m;
    memset(fhat,0,sizeof(fhat));
    memset(ghat,0,sizeof(ghat));
    memset(res,0,sizeof(res));
    memset(h,0,sizeof(h));
    for(int i=0;i<n;++i)
    {
        fhat[__builtin_popcount(i)][i]=f[i];
        ghat[__builtin_popcount(i)][i]=g[i];
    }
    for (int i=0; i<=m; i++) {
        zeta(fhat[i],m);
        zeta(ghat[i],m);
        for (int j=0; j<=i; j++){
            for (int mask = 0; mask < n; mask++){
                h[i][mask] += fhat[j][mask]*ghat[i-j][mask];
            }
        }
        zinv(h[i],m);
    }
    for(int  i=0;i<n;++i)
        res[i]=h[__builtin_popcount(i)][i];
}


