
///*********************************************///
#define MAXP 100000
#define MAXN 1000000
vector<int> prime;
bool isComposite[MAXN];
void LinearSeive(int n)//prime till n-1
{
    fill(isComposite,isComposite+n,false);
    for(int i=2;i<n;++i)
    {
        if(!isComposite[i])
            prime.push_back(i);
        for(int j=0;j<prime.size()&&i*prime[j]<n;++j)
        {
            isComposite[i*prime[j]]=true;
            if(i%prime[j]==0)
                break;
        }
    }
}
void LogSeive(int n)//faster than previous one
{
    fill(isComposite,isComposite+n,false);
    for(int i=2;i<n;++i)
    {
        if(!isComposite[i])
        {
            prime.push_back(i);
            if(1ll*i*i>n)
                continue;
            for(int j=i*i;j<n;j+=i)
                isComposite[j]=true;
        }
    }
}
///*********************************************///
///***********faster linear implementation*****///
#define MAXP 100000
#define MAXN 10000000
vector<int> prime;
int lp[MAXN];//lowest prime that divide i
void LinearSeive(int n)
{
    memset(lp,0,sizeof(int)*n);
    for(int  i=2;i<n;++i)
    {
        if(lp[i]==0)
        {
            lp[i]=i;
            prime.push_back(i);
        }
        for(int j=0;j<(int)prime.size()&&prime[j]<=lp[i]&&i*prime[j]<n;++j)
        {
            lp[i*prime[j]]=prime[j];
        }
    }
}
///*******************************************///
