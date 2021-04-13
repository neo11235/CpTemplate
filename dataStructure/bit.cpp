
#define LSB(i) ((i)&(-(i)))
#define MX_SIZE 200000
ll A[MX_SIZE+1];
ll sum(int i)
{
    ll s=0;
    while(i>0)
    {
        s+=A[i];
        i-=LSB(i);
    }
    return s;
}
void add(int i,ll k)
{
    while(i<=MX_SIZE)
    {
        A[i]+=k;
        i+=LSB(i);
    }
}
///2d version
#define MX_SIZE 1000
ll A[MX_SIZE+1][MX_SIZE+1];
void add(int i,int j,ll val)
{
    int k;
    for(;i<=MX_SIZE;i+=LSB(i))
    {
        for(k=j;k<=MX_SIZE;k+=LSB(k))
        {
            A[i][k]+=val;
        }
    }
}
ll sum(int i,int j)
{
    int k;
    ll s=0;
    for(;i>0;i-=LSB(i))
    {
        for(k=j;k>0;k-=LSB(k))
        {
            s+=A[i][k];
        }
    }
    return s;
}
///Class version
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
            i-=LSB(i);
        }
        return s;
    }
    void add(int i,ll k)
    {
        while(i<=range)
        {
            A[i]+=k;
            i+=LSB(i);
        }
    }
    ~BIT()
    {
        if(A!=NULL)
            delete[] A;
    }
};
