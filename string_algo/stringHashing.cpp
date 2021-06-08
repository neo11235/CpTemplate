unsigned seed = chrono::system_clock::now().time_since_epoch().count();
linear_congruential_engine<uint_fast32_t, 1002517UL, 1001593UL, 2147483647UL> lcg(seed);
int primes_for_mod[]={1000019353,1000001087,1000020353,1000003267,1000000439,1000018001,1000019569,1000020701,1000016929,1000007521,
                        1000007773,1000013323,1000018379,1000017203,1000006211,1000004693,1000013011,1000020829,1000011277,1000007147};
int primes_for_base[]={1831,1061,5927,6689,7529,9719,3917,271,6029,6091,9719,2819,4877,9679,6373,6101,1039,4591,5531};

struct PairHash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const
    {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};
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
void computeRHash(const string& s,long long mod,long long p,vi& hval)
{
    hval[0]=s[0];
    int n=(int)s.length();
    for(int i=1;i<n;i++)
    {
        hval[i]=((ll)hval[i-1]*p+s[i])%mod;
    }
}
void computeFHash(const string&s,long long mod,long long p,vi& hval)
{
    int n=(int)s.length();
    hval[0]=s[0];
    ll pp=1;
    for(int i=1;i<n;i++)
    {
        pp=(pp*p)%mod;
        hval[i]=(hval[i-1]+pp*s[i])%mod;
    }
}
pair<int,int> computeDHash(const string& s,long long p1,long long mod1,long long p2,long long mod2)
{
    return {(int)computeHash(s,p1,mod1),(int)computeHash(s,p2,mod2)};
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
    int n=0;
    SingularHash(){}
    SingularHash(int size,long long mod,long long p)
    {
        reset(size,mod,p);
    }
    SingularHash(const string& s,long long mod,long long p)
    {
        reset(s,mod,p);
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
    void reset(int size,long long mod,long long p)
    {
        destroy();
        n=size;
        this->mod=mod;
        this->p=p;
        allocateMemory();
        pinv=modular_exp(p,mod-2,mod);
    }
    void reset(const string &s,long long mod,long long p)
    {
        destroy();
        n=(int)s.size();
        this->mod=mod;
        this->p=p;
        allocateMemory();
        pinv=modular_exp(p,mod-2,mod);
        construct(s);
    }
    void allocateMemory()
    {
        if(n<=0)
            return;
        hashValue=new int[n];
        pPower=new int[n];
        pInv=new int[n];
    }
    void destroy()
    {
        if(n!=0)
        {
            if(hashValue!=NULL)
                delete[] hashValue;
            if(pPower!=NULL)
                delete[] pPower;
            if(pInv!=NULL)
                delete[] pInv;
        }
    }
    ~SingularHash()
    {
        destroy();
    }
};
void initializeHash(SingularHash& hsh,const string& s)
{
    int cm=lcg()%(sizeof(primes_for_mod)/sizeof(int));
    int cp=lcg()%(sizeof(primes_for_base)/sizeof(int));
    ll mod=primes_for_mod[cm];
    ll p=primes_for_base[cp];
    hsh.reset(s,mod,p);
}
struct DoubleHash{//not tested in contest
    SingularHash sh1,sh2;
    DoubleHash(){}
    DoubleHash(const string& s)
    {
        reset(s);
    }
    DoubleHash(const string&s,DoubleHash& sync)
    {
        sh1.reset(s,sync.sh1.mod,sync.sh1.p);
        sh2.reset(s,sync.sh2.mod,sync.sh2.p);
    }
    void reset(const string & s)
    {
        int cm=lcg()%(sizeof(primes_for_mod)/sizeof(int));
        int cp=lcg()%(sizeof(primes_for_base)/sizeof(int));
        int cm2=cm,cp2=cp;
        while(cm2==cm)
        {
            cm2=lcg()%(sizeof(primes_for_mod)/sizeof(int));
        }
        while(cp2==cp)
        {
            cp2=lcg()%(sizeof(primes_for_base)/sizeof(int));
        }
        sh1.reset(s,primes_for_mod[cm],primes_for_base[cp]);
        sh2.reset(s,primes_for_mod[cm2],primes_for_base[cp2]);
    }
    pii subArray(int l,int r)//inclusive,hash of the subarray [l,r]
    {
        return {sh1.subArray(l,r),sh2.subArray(l,r)};
    }
    pii cyclicSubArray(int l,int r)//inclusive
    {
        return {sh1.cyclicSubArray(l,r),sh2.cyclicSubArray(l,r)};
    }
};
/**************************************************************************/
