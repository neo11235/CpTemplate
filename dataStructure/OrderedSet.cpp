//using dynamic segment tree
template<long long MAX_ELEM_SIZE=1000000000,int MAX_NUM_IN_SET=1000000,int LOG_MAX_ELEM_SIZE=32>
class OrderedSet
{
    struct Element
    {
        int sum,lft,rht;
        Element(){sum=lft=rht=0;}
        Element(int sum,int lft,int rht):sum(sum),lft(lft),rht(rht){}
    };
    Element* data=new Element[LOG_MAX_ELEM_SIZE*MAX_NUM_IN_SET];
    int curSize=1;
    void add(int vindx,long long vl,long long vr,long long indx)
    {
        while(vl!=vr)
        {
            ++data[vindx].sum;
            long long mid=(vl+vr)>>1;
            if(indx<=mid)
            {
                if(!data[vindx].lft)
                    data[vindx].lft=curSize++;
                vr=mid;
                vindx=data[vindx].lft;
            }
            else
            {
                if(!data[vindx].rht)
                    data[vindx].rht=curSize++;
                vl=mid+1;
                vindx=data[vindx].rht;
            }
        }
        ++data[vindx].sum;
    }
    long long query(int vindx,long long vl,long long vr,int i)//find ith element
    {
        if(data[vindx].sum<i)
            return -1;
        while(vl!=vr)
        {
            int lindx=data[vindx].lft;
            if(!lindx)
            {
                vl=((vl+vr)>>1)+1;
                vindx=data[vindx].rht;
                continue;
            }
            if(data[lindx].sum<i)
            {
                i-=data[lindx].sum;
                vl=((vl+vr)>>1)+1;
                vindx=data[vindx].rht;
            }
            else{
                vr=(vl+vr)>>1;
                vindx=lindx;
            }
        }
        return vl;
    }
public:
    OrderedSet(){}
    void insert(long long x)
    {
        add(0,0,MAX_ELEM_SIZE,x);
    }
    long long select(int i)
    {
        return query(0,0,MAX_ELEM_SIZE,i);
    }
    pair<int,int> rank(long long x)//return {-1,-1} if it doesn't exist
    {
        long long vl=0,vr=MAX_ELEM_SIZE;
        int vindx=0;
        int r=0;
        while(vl!=vr)
        {
            long long mid=(vl+vr)>>1;
            if(x<=mid)
            {
                if(!data[vindx].lft)
                    return {-1,-1};
                vr=mid;
                vindx=data[vindx].lft;
            }
            else
            {
                if(!data[vindx].rht)
                    return {-1,-1};
                vl=mid+1;
                r+=data[vindx].lft?data[data[vindx].lft].sum:0;
                vindx=data[vindx].rht;
            }
        }
        return {r,data[vindx].sum};
        //(0 based first position of x,number of occurrence)
    }
    bool exist(long long x)
    {
        return rank(x).first!=-1;
    }
    void clear()
    {
        memset(data,0,sizeof(Element)*curSize);
        curSize=1;
    }
    ~OrderedSet()
    {
        delete[] data;
    }
};
