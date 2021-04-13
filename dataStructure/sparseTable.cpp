///basic sparse table
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
