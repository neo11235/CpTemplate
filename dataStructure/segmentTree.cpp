template<class T>
class segTree// point update range query
{
public:
    T* sgt;
    int n;
    T (*combine)(T,T);
    segTree(T (*combine)(T,T),int sz)
    {
        n=sz;
        sgt=new T[4*sz];
        memset(sgt,0,sizeof(T)*4*sz);
        this->combine=combine;
    }
    segTree(T (*combine)(T,T),T* data,int sz)
    {
        n=sz;
        sgt=new T[4*sz];
        this->combine=combine;
        build(data,1,0,n-1);
    }

    void build(T* data,int v,int vl,int vr)
    {
        if(vl==vr)
        {
            sgt[v]=data[vl];
            return;
        }
        int mid=(vl+vr)/2;
        build(data,2*v,vl,mid);
        build(data,2*v+1,mid+1,vr);
        sgt[v]=combine(sgt[2*v],sgt[2*v+1]);
    }
    void update(int v,int vl,int vr,int pos,T el)
    {
        if(vl==vr)
        {
            sgt[v]=el;
            return;
        }
        int mid=(vl+vr)/2;
        if(pos<=mid)
            update(2*v,vl,mid,pos,el);
        else
            update(2*v+1,mid+1,vr,pos,el);
        sgt[v]=combine(sgt[2*v],sgt[2*v+1]);
    }
    void update(int pos,T el)
    {
        update(1,0,n-1,pos,el);
    }
    T query(int v,int vl,int vr,int l,int r)
    {
        if(vl==l&&vr==r)
            return sgt[v];
        int mid=(vl+vr)/2;
        if(r<=mid)
            return query(2*v,vl,mid,l,r);
        else if(l>mid)
            return query(2*v+1,mid+1,vr,l,r);
        else
            return combine(query(2*v,vl,mid,l,mid),query(2*v+1,mid+1,vr,mid+1,r));
    }
    T query(int l,int r)
    {
        return query(1,0,n-1,l,r);
    }
};


template<class T,class dT>
class segTree// point update range query
{
public:
    T* sgt;
    dT* data;
    int n;
    T (*combine)(T,T);
    T (*dtToT)(dT);
    segTree()
    {
        data=NULL;
        sgt=NULL;
        combine=NULL;
        dtToT=NULL;
        n=0;
    }
    segTree(T (*combine)(T,T),T (*dtToT)(dT),int sz)
    {
        n=sz;
        sgt=new T[4*sz];
        memset(sgt,0,sizeof(T)*4*sz);
        data=NULL;
        this->combine=combine;
        this->dtToT=dtToT;
    }
    segTree(T (*combine)(T,T),T (*dtToT)(dT),dT* data,int sz)
    {
        n=sz;
        sgt=new T[4*sz];
        this->combine=combine;
        this->dtToT=dtToT;
        this->data=new dT[sz];
        for(int i=0;i<sz;i++)
        {
            this->data[i]=data[i];
        }
        build(1,0,n-1);
    }

    void build(int v,int vl,int vr)
    {
        if(vl==vr)
        {
            sgt[v]=dtToT(data[vl]);
            return;
        }
        int mid=(vl+vr)/2;
        build(2*v,vl,mid);
        build(2*v+1,mid+1,vr);
        sgt[v]=combine(sgt[2*v],sgt[2*v+1]);
    }
    void update(int v,int vl,int vr,int pos,T el)
    {
        if(vl==vr)
        {
            sgt[v]=el;
            return;
        }
        int mid=(vl+vr)/2;
        if(pos<=mid)
            update(2*v,vl,mid,pos,el);
        else
            update(2*v+1,mid+1,vr,pos,el);
        sgt[v]=combine(sgt[2*v],sgt[2*v+1]);
    }
    void update(int pos,T el)
    {
        update(1,0,n-1,pos,el);
    }
    void update(int pos,dT el)
    {
        update(1,0,n-1,pos,dtToT(el));
    }
    T query(int v,int vl,int vr,int l,int r)
    {
        if(vl==l&&vr==r)
            return sgt[v];
        int mid=(vl+vr)/2;
        if(r<=mid)
            return query(2*v,vl,mid,l,r);
        else if(l>mid)
            return query(2*v+1,mid+1,vr,l,r);
        else
            return combine(query(2*v,vl,mid,l,mid),query(2*v+1,mid+1,vr,mid+1,r));
    }
    T query(int l,int r)
    {
        return query(1,0,n-1,l,r);
    }
    ~segTree()
    {
        if(sgt!=NULL)
            delete[] sgt;
        if(data!=NULL)
            delete[] data;
    }
};

///lazy propagation
template<class T>
class SegTree{
    T* sgt;
    ///combine must clear out any unpropagated value
    T (*combine)(T,T);
    T (*propagate)(T to,T from,int);
    int n;
public:
    SegTree(int sz,T(*combine)(T,T),T(*propagate)(T,T,int),T* data=NULL)
    {
        this->combine=combine;
        this->propagate=propagate;
        n=sz;
        sgt=new T[4*sz];
        if(data!=NULL)
            build(1,0,n-1,data);
    }
    void build(int v,int vl,int vr,T* data)
    {
        if(vl==vr)
        {
            sgt[v]=data[vl];
            return;
        }
        int mid=(vl+vr)/2;
        build(2*v,vl,mid,data);
        build(2*v+1,mid+1,vr,data);
        sgt[v]=combine(sgt[2*v],sgt[2*v+1]);
    }
    void update(int v,int vl,int vr,int l,int r,T unp)
    {
        if(vl==l&&vr==r)
        {
            sgt[v]=propagate(sgt[v],unp,r-l+1);
            return;
        }
        int mid=(vl+vr)/2;
        sgt[2*v]=propagate(sgt[2*v],sgt[v],mid-vl+1);
        sgt[2*v+1]=propagate(sgt[2*v+1],sgt[v],vr-mid);
        if(r<=mid)
            update(2*v,vl,mid,l,r,unp);
        else if(l>mid)
            update(2*v+1,mid+1,vr,l,r,unp);
        else
        {
            update(2*v,vl,mid,l,mid,unp);
            update(2*v+1,mid+1,vr,mid+1,r,unp);
        }
        sgt[v]=combine(sgt[2*v],sgt[2*v+1]);
    }
    void update(int l,int r,T unp)
    {
        update(1,0,n-1,l,r,unp);
    }
    T query(int v,int vl,int vr,int l,int r)
    {
        if(vl==l&&vr==r)
        {
            return sgt[v];
        }
        int mid=(vl+vr)/2;
        sgt[2*v]=propagate(sgt[2*v],sgt[v],mid-vl+1);
        sgt[2*v+1]=propagate(sgt[2*v+1],sgt[v],vr-mid);
        sgt[v]=combine(sgt[2*v],sgt[2*v+1]);
        if(r<=mid)
            return query(2*v,vl,mid,l,r);
        else if(l>mid)
            return query(2*v+1,mid+1,vr,l,r);
        else
            return combine(query(2*v,vl,mid,l,mid),query(2*v+1,mid+1,vr,mid+1,r));
    }
    T query(int l,int r)
    {
        return query(1,0,n-1,l,r);
    }
    ~SegTree()
    {
        if(n!=0&&sgt!=NULL)
            delete[] sgt;
    }
};
