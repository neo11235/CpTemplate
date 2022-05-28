//able to compute a*b%mod a,b<2^63
ll moduloMultiplication(ll a,ll b,ll mod){
    ll res = 0;a %= mod;
    while (b){
        if(b&1)res=(res+a)%mod;
        a=(2*a)%mod;b>>=1;
    }
    return res;
}
ll modular_exp(ll a,ll b,ll mod){
    ll ans=1;
    while(b>0){
        if(b&1)ans=moduloMultiplication(ans,a,mod);
        b=b>>1;
        a=moduloMultiplication(a,a,mod);
    }
    return ans;
}
bool farmatsTest(ll n,int it=10)
{
    if(n<4)return n==2||n==3;
    for(int i=0;i<it;i++)
    {
        ll a=2+rand()%(n-3);
        if(modular_exp(a,n-1,n)!=1)
            return false;
    }
    return true;
}
/**********miller rabin********************/
using u64 = uint64_t;
using u128=__uint128_t;
u64 modular_exp(u64 a,u64 b,u64 mod){
    ll ans=1;
    while(b>0){
        if(b&1)ans=(__uint128_t)ans*a%mod;
        b=b>>1;
        a=(__uint128_t)a*a%mod;
    }
    return ans;
}
bool check_composite(u64 n,u64 a,u64 d,int s)
{
    u64 x=modular_exp(a,d,n);
    if(x==1||x==n-1)
        return false;
    for(int r=1;r<s;r++)
    {
        x=(u128)x*x%n;
        if(x==n-1)
            return false;
    }
    return true;
}
bool millerRabin(u64 n)
{
    if(n<2)return false;
    u64 d=n-1;
    int r=0;
    while(!(d&1))
    {
        d=d>>1;
        r++;
    }
    for(int a:{2,3,5,7,11,13,17,19,23,29,31,37})
    {
        if(n==a)
            return true;
        if(check_composite(n,a,d,r))
            return false;
    }
    return true;
}
