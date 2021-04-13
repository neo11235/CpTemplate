class PersistentDsu{
public:
    struct DsuSave{
        int u,rnku,v,rnkv;
        DsuSave(){}
        DsuSave(int u,int rnku,int v,int rnkv):u(u),rnku(rnku),v(v),rnkv(rnkv){}
    };
    stack<DsuSave> op;
    int* p,*rnk,ntree,n;
    PersistentDsu()
    {
        n=0;
    }
    void initialize()
    {
        for(int i=0;i<n;i++)
            p[i]=i;
        memset(rnk,0,sizeof(int)*n);
    }
    PersistentDsu(int n)
    {
        this->n=n;
        p=new int[n];
        rnk=new int[n];
        ntree=n;
        initialize();
    }
    void resize(int nn)
    {
        if(n)
        {
            delete[] p;
            delete[] rnk;
        }
        p=new int[nn];
        rnk=new int[nn];
        ntree=nn;
        n=nn;
        initialize();
        while(!op.empty())
        {
            op.pop();
        }
    }
    int findSet(int i)
    {
        while(i!=p[i])
        {
            i=p[i];
        }
        return i;
    }
    bool unionSet(int u,int v)//keep track of which union operation actually changed the sets
    {
        u=findSet(u);
        v=findSet(v);
        if(u==v)
            return false;
        if(rnk[u]>rnk[v])
            swap(u,v);
        op.push(DsuSave(u,rnk[u],v,rnk[v]));
        if(rnk[u]==rnk[v])
        {
            rnk[v]++;
        }
        p[u]=v;
        ntree--;
        return true;
    }
    bool rollback()//rollback last operation;
    {
        if(op.empty())
            return false;
        DsuSave pstate=op.top();
        op.pop();
        p[pstate.u]=pstate.u;
        rnk[pstate.v]=pstate.rnkv;
        ntree++;
        return true;
    }
};
