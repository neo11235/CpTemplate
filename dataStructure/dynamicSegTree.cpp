///point update range sum
///all public indexing 0 based
template<typename T,long long MAX_ELEM_SIZE=1000000000,int MAX_NUM_IN_SET=200000,int LOG_MAX_ELEM_SIZE=32>
class DynSegTree{
    struct Element
    {
        T sum;
        int lft,rht;
        Element(){sum=lft=rht=0;}
        Element(T sum,int lft,int rht):sum(sum),lft(lft),rht(rht){}
    };
    Element* tree=new Element[MAX_NUM_IN_SET*LOG_MAX_ELEM_SIZE];
    int curSize=1;
    void update(int v,long long vl,long long vr,long long indx,T val)
    {
        if(vl==vr)
        {
            tree[v].sum=val;
            return;
        }
        long long mid=(vl+vr)/2;
        if(indx<=mid)
        {
            if(!tree[v].lft)
                tree[v].lft=curSize++;
            update(tree[v].lft,vl,mid,indx,val);
        }
        else
        {
            if(!tree[v].rht)
                tree[v].rht=curSize++;
            update(tree[v].rht,mid+1,vr,indx,val);
        }
        tree[v].sum=(tree[v].lft?tree[tree[v].lft].sum:0)+
        (tree[v].rht?tree[tree[v].rht].sum:0);
    }
    T sum(int v,long long vl,long long vr,long long l,long long r)
    {
        if(vl==l&&vr==r)
            return tree[v].sum;
        long long mid=(vl+vr)/2;
        if(r<=mid)
        {
            if(!tree[v].lft)
                return (T)0;
            return sum(tree[v].lft,vl,mid,l,r);
        }
        else if(l>mid)
        {
            if(!tree[v].rht)
                return (T)0;
            return sum(tree[v].rht,mid+1,vr,l,r);
        }
        else
        {
            return (tree[v].lft?sum(tree[v].lft,vl,mid,l,mid):0)
                +(tree[v].rht?sum(tree[v].rht,mid+1,vr,mid+1,r):0);
        }
    }

public:
    DynSegTree(){}
    void update(long long indx,T val)
    {
        assert(indx>=0&&indx<=MAX_ELEM_SIZE);
        update(0,0,MAX_ELEM_SIZE,indx,val);
    }
    T sum(long long l,long long r)//inclusive
    {

        assert(l>=0&&r>=0&&l<=MAX_ELEM_SIZE&&r<=MAX_ELEM_SIZE);
        if(l>r)
            return (T)0;
        return sum(0,0,MAX_ELEM_SIZE,l,r);
    }
    void clear()
    {
        memset(tree,0,sizeof(Element)*curSize);
        curSize=1;
    }
    ~DynSegTree()
    {
        delete[] tree;
    }
};
