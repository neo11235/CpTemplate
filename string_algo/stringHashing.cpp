int primes_for_mod[]={1000019353,1000001087,1000020353,1000003267,1000000439,1000018001,1000019569,1000020701,1000016929,1000007521,
                        1000007773,1000013323,1000018379,1000017203,1000006211,1000004693,1000013011,1000020829,1000011277,1000007147};
int primes_for_base[]={1831,1061,5927,6689,7529,9719,3917,271,6029,6091,9719,2819,4877,9679,6373,6101,1039,4591,5531};


long long computeHash(const string& s,const long long p,const long long mod)
{
    long long res=0;
    long long pp=1;
    for(char c:s)
    {
        res=(res+pp*(c-'a'+1))%mod;
        pp=(pp*p)%mod;
    }
    return res;
}

/**class based implementation***/
ll modular_exp(ll a,ll b,ll mod){//mod should be <32 bit
    ll ans=1;
    while(b>0){
        if(b&1)ans=(ans*a)%mod;
        b=b>>1;
        a=(a*a)%mod;
    }
    return ans;
}
//string hashing,building O(n),query O(1),memory O(n),tested on cf
struct SingularHash{//use a single prime number
    const char sub='a';
    long long mod,p,pinv;
    int* hashValue=NULL;
    int* pPower=NULL;
    int* pInv=NULL;
    int n;
    SingularHash()
    {
        n=-1;
    }
    SingularHash(int size,long long mod,long long p)
    {
        n=size;
        this->mod=mod;
        this->p=p;
        pinv=modular_exp(p,mod-2,mod);
        hashValue=new int[size];
        pPower=new int[size];
        pInv=new int[size];
    }
    SingularHash(const string& s,long long mod,long long p)
    {
        n=(int)s.size();
        this->mod=mod;
        this->p=p;
        hashValue=new int[n];
        pPower=new int[n];
        pInv=new int[n];
        pinv=modular_exp(p,mod-2,mod);
        construct(s);
    }
    void construct(const string& s)
    {
        pPower[0]=pInv[0]=1;
        hashValue[0]=s[0]-sub+1;
        int slen=(int)s.length();
        for(int i=1;i<slen;i++)
        {
            pPower[i]=(pPower[i-1]*p)%mod;
            pInv[i]=(pInv[i-1]*pinv)%mod;
            hashValue[i]=(hashValue[i-1]+(ll)(s[i]-sub+1)*pPower[i])%mod;
        }
    }
    int subArray(int l,int r)//inclusive,hash of the subarray [l,r]
    {
        if(l>r)
            swap(l,r);
        ll ans=(hashValue[r]-(l==0?0:hashValue[l-1])+mod)%mod;
        ans=(ans*pInv[l])%mod;
        return (int)ans;
    }
    int cyclicSubArray(int l,int r)
    {
        if(l<=r)
            return subArray(l,r);
        long long res=subArray(l,n-1);
        return (int)((res+(((long long)hashValue[r]*pPower[n-l])%mod))%mod);

    }
    ~SingularHash()
    {
        if(n!=-1)
        {
            if(hashValue!=NULL)
                delete[] hashValue;
            if(pPower!=NULL)
                delete[] pPower;
            if(pInv!=NULL)
                delete[] pInv;
        }
    }
};
/**************************************************************************/
