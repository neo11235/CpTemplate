#ifndef MATH_EX_H_INCLUDED
#define MATH_EX_H_INCLUDED
using namespace std;
#include "E:\codeblocksfile\c++\data_structure_tool\prime.h"
/****modular inverse O(logn)****/
template <class T>T n_inverse_mod_m(T n,T m){
    T rn_1,rn,sn_1,sn,tn_1,tn,tr,ts,tt,q;
    rn_1=n;sn_1=1;tn_1=0;
    rn=m;sn=0;tn=1;
    while(1){
        tr=rn_1%rn;
        q=(rn_1-tr)/rn;
        ts=sn_1-(q*sn);
        tt=tn_1-(q*tn);
        if(tr==0){
            return (sn+m)%m;
        }
        sn_1=sn;sn=ts;
        tn_1=tn;tn=tt;
        rn_1=rn;rn=tr;
    }
}
template <class T>pair<T,T> extended_euclid(T n,T m){//returns <u,v> such that nu+mv=(n,m)
    T rn_1,rn,sn_1,sn,tn_1,tn,tr,ts,tt,q;
    rn_1=n;sn_1=1;tn_1=0;
    rn=m;sn=0;tn=1;
    while(1){
        tr=rn_1%rn;
        q=(rn_1-tr)/rn;
        ts=sn_1-(q*sn);
        tt=tn_1-(q*tn);
        if(tr==0){
            return mp(sn,tn);
        }
        sn_1=sn;sn=ts;
        tn_1=tn;tn=tt;
        rn_1=rn;rn=tr;
    }
}
/*********eular's totient O(root(n))*********/
template<class T> T phi(T n){
    T t=n,l=sqrt((long double)n),i;
    for(i=2;i<=l;i++){
        if((t%i)==0){
            n/=i;
            n*=(i-1);
            while((t%i)==0)t/=i;
        }
    }
    if(t!=1){
        n/=t;
        n*=(t-1);
    }
    return n;
}
template<class T> factorial(T n){
    T i=(T)2,ans=(T)1;
    for(;i<=n;i++){
        ans*=i;
    }
    return ans;
}
int64_t _modulus(int64_t number,int64_t power,int64_t mod){//return=(a^b)%mod
    char bin_data[65];
    int64_t curent_number=1;
    int j=0;
    lltoa(power,bin_data,2);
    while(bin_data[j]!='\0'){
        if(bin_data[j]=='1'){
            curent_number=(curent_number*curent_number)%mod;
            curent_number=(curent_number*number)%mod;
        }
        else{
            curent_number=(curent_number*curent_number)%mod;
        }
        j++;
    }
    return curent_number;
}
ll modular_exp(ll a,ll b,ll mod){//mod should be <32 bit
    ll ans=1;
    while(b>0){
        if(b&1)ans=(ans*a)%mod;
        b=b>>1;
        a=(a*a)%mod;
    }
    return ans;
}
/*********finding all factor below n in O(nlogn)*********/
int *pfactor;
void build(int n){//prime factor of every number below n
    pfactor=new int[n+1];
    memset(pfactor,0,sizeof(int)*(n+1));
    int i,j;
    for(i=2;i<=n;i++){
        if(pfactor[i]==0){
            for(j=i;j<=n;j+=i){
                pfactor[j]=i;
            }
        }
    }
    return;
}
int get_p_factor(vector<int>& pf,vector<int>& pfp,int n){//pf and pfp must have size>log(n) returns number of prime factor
    int i=0;
    int j,pw;
    while(n>1){
        j=pfactor[n];
        pw=0;
        while(!(n%j)){
            n/=j;
            pw++;
        }
        pf[i]=j;
        pfp[i]=pw;
        i++;
    }
    return i;
}
int get_all_factor(vector<int>& pf,vector<int>& pfp,int sz,vector<int> &vct){
    vct[0]=1;
    int i,j,k,l,r,s=1;
    for(i=0;i<sz;i++){
        l=0;
        for(j=0;j<pfp[i];j++){
            r=s;
            for(k=l;k<r;k++,s++){
                vct[s]=(vct[k]*pf[i]);
            }
            l=r;
        }
    }
    return s;
}
/******************/
int get_p_factor(vector<ll>& pf,vector<ll>& pfp,ll n){//pf and pfp must have size>log(n) returns number of prime factor

    ll lim=sqrt((long double)n);
    ll i;
    int j=0;
    int pw;
    for(i=2;i<=lim;i++){
        if(!(n%i)){
            pf[j]=i;
            pw=0;
            while(!(n%i)){
                n/=i;
                pw++;
            }
            pfp[j]=pw;
            j++;
        }
    }
    if(n>1){
        pf[j]=n;
        pfp[j]=1;
        j++;
    }
    return j;
}
int get_all_factor(vector<ll>& pf,vector<ll>& pfp,int sz,vector<ll> &vct,vector<ll>& sigma){
    vct[0]=1;
    sigma[0]=1;
    int i,j,k,l,r,s=1,fr;
    for(i=0;i<sz;i++){
        l=0;
        for(j=0;j<pfp[i];j++){
            fr=0;
            r=s;
            for(k=l;k<r;k++,s++,fr++){
                vct[s]=(vct[k]*pf[i]);
                sigma[s]=(sigma[fr]*(j+2));
            }
            l=r;
        }
    }
    return s;
}
/********nck mod p**********/
ll *fact,*factinv;
const ll p=1000000007;
void build(int n){
    fact=new ll[n+1];
    factinv=new ll[n+1];
    fact[0]=factinv[0]=1;
    for(int i=1;i<=n;i++){
        fact[i]=(fact[i-1]*(ll)i)%p;
        factinv[i]=n_inverse_mod_m(fact[i],p);
    }
    return;
}
ll nck_mod_p(int n,int k){
    ll ans=(fact[n]*factinv[k])%p;
    ans=(ans*factinv[n-k])%p;
    return ans;
}

/******************/
/********phi(eular totient function) below n in O(nlogn)**********/
int *phi;
void build(int n){
    phi=new int[n+1];
    memset(phi,0,sizeof(int)*(n+1));
    ll i,j,l;
    l=(int)sqrt((double)n);
    for(i=2;i<=l;i++){
        if(!phi[i]){
            for(j=i;j<=n;j+=i){
                phi[j]=-i;
            }
            for(j=i;j<=n;j*=i){
                phi[j]=j-j/i;
            }
        }
    }
    for(;i<=n;i++){
        if(!phi[i]){
            phi[i]=i-1;
        }
    }
    phi[1]=1;
    for(i=2;i<=n;i++){
        if(phi[i]<0){
            phi[i]=-phi[i];
            j=1;
            l=i;
            while(!(l%phi[i])){
                l/=phi[i];
            }
            phi[i]=phi[i/l]*phi[l];
        }
    }
}
/******************/
long long moduloMultiplication(long long a,long long b,long long mod){//able to compute a*b%mod a,b<2^63
    long long res = 0;
    a %= mod;
    while (b){
        if(b&1)res=(res+a)%mod;
        a=(2*a)%mod;
        b>>=1;
    }
    return res;
}
/***************************/
/************shanks babystep giant step algorithm*******/
ll modular_exp(ll a,ll b,ll mod){//mod should be <32 bit
    ll ans=1;
    while(b>0){
        if(b&1)ans=(ans*a)%mod;
        b=b>>1;
        a=(a*a)%mod;
    }
    return ans;
}
ll dlog(ll a,ll b,ll mod){
    ll n,p,q;
    n=(ll)sqrt((double)mod)+1ll;
    ll an=modular_exp(a,n,mod);
    map<ll,ll> map_;
    ll cur=an;
    for(p=1;p<=n;p++){
        if(map_.find(cur)==map_.end()){
            map_.insert(mp(cur,p));
        }
        cur=(cur*an)%mod;
    }
    cur=b;
    ll mn=infl;
    for(q=0;q<=n;q++){
        if(map_.find(cur)!=map_.end()){
            mn=min((n*map_[cur])-q,mn);
        }
        cur=(cur*a)%mod;
    }
    if(mn==infl)return -1;
    else return mn;
}
/*********************************************/
/*********************prime************************/
bitset<10000020> bl;
int prime[664580];
void build(void){
    bl.set();
    int i,j;
    int lim=(int)sqrt(10000020.0);
    for(i=2;i<=lim;++i){
        if(bl[i]){
            for(j=i+i;j<10000020;j+=i)bl[j]=0;
        }
    }
    j=0;
    for(i=2;i<10000020;i++){
        if(bl[i]){
            prime[j]=i;
            j++;
        }
    }
    return;
}
void mark_prime(int l,int r){//inclusive [l,r-1] assumes prime array to be filled//bitset is marked indexing 0=~l//r-l<10^7
    int lim=(int)sqrt((double)r);
    int i,j;
    bl.set();
    for(i=0;prime[i]<=lim;++i){
        j=l/prime[i];
        if(l%prime[i])j++;
        j*=prime[i];
        if(j==prime[i])j+=prime[i];
        j-=l;
        for(;j<(r-l);j+=prime[i]){
            bl[j]=0;
        }
    }
    return;
}
/***************************************/
/****************mobius function***********************/
int* mob;
void build(int n){
    mob=new int[n+1];
    memset(mob,0,sizeof(int)*(n+1));
    ll i,j,l=(ll)sqrt((double)(n+1));
    for(i=2;i<=l;i++){
        if(!mob[i]){
            for(j=i+i;j<=n;j+=i){
                mob[j]=i;
            }
        }
    }
    for(i=2;i<=n;i++){
        if(!mob[i]){
            mob[i]=-1;
        }
        else{
            j=i;
            while(!(j%mob[i])){
                j/=mob[i];
            }
            mob[i]=mob[j]*mob[i/j];
        }
    }
    mob[1]=1;
    return;
}
/***************************************************/
int *mf;
int base_case(int p,int k){//base case for p^k
    return k+1;
}
void comp_mult_func(int n){
    mf=new int[n+1];
    memset(mf,-1,sizeof(int)*(n+1));
    int i,k,k2;
    ll l;
    mf[1]=1;
    for(i=2;i<=n;i++){
        if(mf[i]==-1){
            for(l=i+i;l<=n;l+=i)mf[l]=-i;
            l=i;
            k=1;
            while(l<=(ll)n){
                mf[l]=base_case(i,k);
                k++;
                l*=i;
            }
        }
    }
    for(i=2;i<=n;i++){
        if(mf[i]<0){
            mf[i]=-mf[i];
            k=i;
            while(!(k%mf[i])){
                k/=mf[i];
            }
            mf[i]=mf[k]*mf[i/k];
        }
    }
    return;
}
/*********************************************/
#endif // MATH_EX_H_INCLUDED
