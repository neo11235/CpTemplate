class PSeive
{
    int *bl=NULL;
    int sz;
public:
    PSeive(int sz){
        bl=new int[sz+1];
        memset(bl,0,sizeof(int)*(sz+1));
        this->sz=sz+1;
    }
    int getPrimes(vector<int>& out)
    {
        int i,j,nprimes=0;
        for(i=2;i<sz;i++)
        {
            if(!bl[i])
            {
                for(j=i<<1;j<sz;j+=i)
                {
                    bl[j]=1;
                }
                out.push_back(i);
            }
        }
        return out.size();
    }
    int primeFactorize(vector<int>& primes,vector<ll>& pf,vector<int>& pfp,ll n)
    {
        int lim=(int)sqrt((double)n);
        int i=0,j=0;
        for(i=0;i<(int)primes.size()&&primes[i]<=n&&primes[i]<=lim;i++)
        {
            if(!(n%primes[i]))
            {
                int cnt=0;
                while(!(n%primes[i]))
                {
                    n/=primes[i];
                    cnt++;
                }
                pf[j]=primes[i];
                pfp[j++]=cnt;
            }
        }
        if(n>1)
        {
            pf[j]=n;
            pfp[j++]=1;
        }
        return j;
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
    ~PSeive()
    {
        if(bl!=NULL)
            delete[] bl;
    }
};
