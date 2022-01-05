///basic sparse table
///runtime build O(nlogn)
///memory O(nlogn)
///query O(1)
///queryDisjoint O(logn)
template<class T>
class sparseTable
{
    T** table;
    ll (*combine)(T,T);
    int n,l;
public:
    sparseTable(int n,int l,vector<T>&data,ll (*combine)(T,T))
    {
        this->n=n;
        this->l=l;
        this->combine=combine;
        table=new T*[n];
        for(int i=0;i<n;i++)
        {
            table[i]=new T[l];
            table[i][0]=data[i];
        }
        build();

    }
    sparseTable(int n,int l,T* data,ll (*combine)(T,T))
    {
        this->n=n;
        this->l=l;
        this->combine=combine;
        table=new T*[n];
        for(int i=0;i<n;i++)
        {
            table[i]=new T[l];
            table[i][0]=data[i];
        }
        build();
    }
    void build()
    {
        for(int j=1;j<l;j++)
        {
            for(int i=0;i<n;i++)
            {
                table[i][j]=table[i][j-1];
                if(i+(1<<(j-1))<n)
                    table[i][j]=combine(table[i][j],table[i+(1<<(j-1))][j-1]);
            }
        }
    }
    T query(int lpoint,int rpoint)
    {
        int nn=rpoint-lpoint+1;
        int j=0;
        while(j<l&&(1<<j)<=nn)
            j++;
        j--;
        return combine(table[lpoint][j],table[rpoint-(1<<j)+1][j]);
    }
};

/////better implementation////////////

template<class T,T (*combine)(T,T),int n,int l>
class SparseTable
{
    T table[n][l];
    int logTable[n+1];
    template<class T2>
    void init(T2 data,int len)
    {
        table[0][0]=data[0];
        logTable[0]=-1;
        for(int i=1;i<len;i++)
        {
            table[i][0]=data[i];
            logTable[i]=logTable[i/2]+1;
        }
        logTable[len]=logTable[len/2]+1;
    }
public:
    SparseTable(){}
    template<class T2>
    SparseTable(T2 data,int len)///data either T* or vector<T>&
    {
        init(data,len);
        build();
    }
    template<class T2>
    void rebuild(T2 data,int len)
    {
        init(data,len);
        build();
    }
    void build()
    {
        for(int j=1;j<l;j++)
        {
            for(int i=0;i<n;i++)
            {
                table[i][j]=table[i][j-1];
                if(i+(1<<(j-1))<n)
                    table[i][j]=combine(table[i][j],table[i+(1<<(j-1))][j-1]);
            }
        }
    }
    T query(int lpoint,int rpoint)
    {
        int j=logTable[rpoint-lpoint+1];
        return combine(table[lpoint][j],table[rpoint-(1<<j)+1][j]);
    }
    ///if combine operation have to be disjoint
    ///like sum query
    T queryDisjoint(int lpoint,int rpoint)
    {
        T res(0);
        for(int j=l-1;j>=0;--j)
        {
            if((1<<j)<=rpoint-lpoint+1)
            {
                res=combine(res,table[lpoint][j]);
                lpoint+=1<<j;
            }
        }
        return res;
    }
};

///**************************************************///
