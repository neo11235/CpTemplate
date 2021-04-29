/**first implementation**/
struct Line{
    long long m,c;//mx+c
    Line(){
        m=c=infl;
    }
    Line(ll m,ll c):m(m),c(c){}
    long long operator()(long long x)
    {
        return m*x+c;
    }
    bool parallel(Line l)
    {
        return m==l.m;
    }
    pair<long double,long double> intersect(Line l)//assuming not parallel
    {
        long double x,y;
        x=(long double)(l.c-c)/(m-l.m);
        y=(long double)m*x+c;
        return {x,y};
    }
};
//minimum lct
Line lct[4000000];
#define infl 0x7fffffffffffffff
void update(int v,int vl,int vr,Line nl)
{
    if(lct[v].m==infl)
    {
        lct[v]=nl;
        return;
    }
    if(vl==vr)
    {
        if(lct[v](vl)>nl(vl))
        {
            lct[v]=nl;
        }
        return;
    }
    if(lct[v].m>nl.m)
        swap(lct[v],nl);
    int mid=(vl+vr)/2;
    if(nl(mid)>lct[v](mid))
    {
        update(2*v,vl,mid,nl);
    }
    else
    {
        swap(lct[v],nl);
        update(2*v+1,mid+1,vr,nl);
    }
}
ll query(int v,int vl,int vr,int indx)
{
    if(vl==vr)
    {
        if(lct[v].m==infl)
            return infl;
        return lct[v](vl);
    }
    int mid=(vl+vr)/2;
    ll res=infl;
    if(lct[v].m!=infl)
        res=lct[v](indx);
    if(indx<=mid)
        return min(res,query(2*v,vl,mid,indx));
    else
        return min(res,query(2*v+1,mid+1,vr,indx));
}
void clearlct()
{
    for(int i=0;i<4000000;i++)
        lct[i].m=lct[i].c=infl;
}
///********************************////////

/**Class based implementation**/
class LCT{
    Line* lct;
    int n;
    bool mntree;
    void updateMin(int v,int vl,int vr,Line nl)
    {
        if(lct[v].m==infl)
        {
            lct[v]=nl;
            return;
        }
        if(vl==vr)
        {
            if(lct[v](vl)>nl(vl))
                lct[v]=nl;
            return;
        }
        if(lct[v].m>nl.m)
            swap(lct[v],nl);
        int mid=(vl+vr)/2;
        if(nl(mid)>lct[v](mid))
        {
            updateMin(2*v,vl,mid,nl);
        }
        else
        {
            swap(lct[v],nl);
            updateMin(2*v+1,mid+1,vr,nl);
        }
    }
    void updateMax(int v,int vl,int vr,Line nl)
    {
        if(lct[v].m==infl)
        {
            lct[v]=nl;
            return;
        }
        if(vl==vr)
        {
            if(lct[v](vl)<nl(vl))
                lct[v]=nl;
            return;
        }
        if(lct[v].m>nl.m)
        {
            swap(lct[v],nl);
        }
        int mid=(vl+vr)/2;
        if(nl(mid)>lct[v](mid))
        {
            swap(lct[v],nl);
            updateMax(2*v,vl,mid,nl);
        }
        else
        {
            updateMax(2*v+1,mid+1,vr,nl);
        }
    }
    ll queryMin(int v,int vl,int vr,int indx)
    {
        if(vl==vr)
        {
            if(lct[v].m==infl)
                return infl;
            return lct[v](vl);
        }
        int mid=(vl+vr)/2;
        ll res=infl;
        if(lct[v].m!=infl)
            res=lct[v](indx);
        if(indx<=mid)
            return min(res,queryMin(2*v,vl,mid,indx));
        else
            return min(res,queryMin(2*v+1,mid+1,vr,indx));
    }
    ll queryMax(int v,int vl,int vr,int indx)
    {
        if(vl==vr)
        {
            if(lct[v].m==infl)
                return -infl;
            return lct[v](vl);
        }
        int mid=(vl+vr)/2;
        ll res=-infl;
        if(lct[v].m!=infl)
            res=lct[v](indx);
        if(indx<=mid)
            return max(res,queryMax(2*v,vl,mid,indx));
        else
            return max(res,queryMax(2*v+1,mid+1,vr,indx));
    }
public:
    LCT(int sz,bool minTree=true)
    {
        n=sz;
        mntree=minTree;
        lct=new Line[4*n];
    }
    void update(Line nl)
    {
        if(mntree)
            updateMin(1,0,n-1,nl);
        else
            updateMax(1,0,n-1,nl);
    }
    ll query(int x)
    {
        if(mntree)
            return queryMin(1,0,n-1,x);
        return queryMax(1,0,n-1,x);
    }
    ~LCT()
    {
        if(lct!=NULL)
            delete[] lct;
    }

};
/*****************************/


/** super cool dynamic lct****/

#define LL_MAX 0x7fffffffffffffff
struct Line{
    long long m,c;//mx+c
    Line(){
        m=c=LL_MAX;
    }
    Line(ll m,ll c):m(m),c(c){}
    long long operator()(long long x)
    {
        return m*x+c;
    }
    bool parallel(Line l)
    {
        return m==l.m;
    }
    pair<long double,long double> intersect(Line l)//assuming not parallel
    {
        long double x,y;
        x=(long double)(l.c-c)/(m-l.m);
        y=(long double)m*x+c;
        return {x,y};
    }
};
struct LctElement{
    Line l;
    LctElement *lft,*rht;
    LctElement()
    {
        lft=rht=NULL;
    }
};
class DynamicLCT{
    LctElement* root;
    bool minTree;
    void updateMin(LctElement* v,int vl,int vr,Line nl)
    {
        if(v->l.m==LL_MAX)
        {
            v->l=nl;
            return;
        }
        if(vl==vr)
        {
            if(nl(vl)<v->l(vl))
            {
                v->l=nl;
            }
            return;
        }
        if(v->l.m>nl.m)
        {
            swap(v->l,nl);
        }
        int mid=(vl+vr)/2;
        if(nl(mid)>v->l(mid))
        {
            if(v->lft==NULL)
                v->lft=new LctElement();
            updateMin(v->lft,vl,mid,nl);
        }
        else
        {
            swap(v->l,nl);
            if(v->rht==NULL)
                v->rht=new LctElement();
            updateMin(v->rht,mid+1,vr,nl);
        }
    }
    void updateMax(LctElement* v,int vl,int vr,Line nl)
    {
        if(v->l.m==LL_MAX)
        {
            v->l=nl;
            return;
        }
        if(vl==vr)
        {
            if(nl(vl)>v->l(vl))
            {
                v->l=nl;
            }
            return;
        }
        if(v->l.m>nl.m)
        {
            swap(v->l,nl);
        }
        int mid=(vl+vr)/2;
        if(nl(mid)>v->l(mid))
        {
            swap(v->l,nl);
            if(v->lft==NULL)
                v->lft=new LctElement();
            updateMax(v->lft,vl,mid,nl);
        }
        else
        {
            if(v->rht)
                v->rht=new LctElement();
            updateMax(v->rht,mid+1,vr,nl);
        }
    }
    ll queryMin(LctElement* v,int vl,int vr,ll x)
    {
        if(v==NULL)
            return LL_MAX;
        if(vl==vr)
        {
            if(v->l.m==LL_MAX)
                return LL_MAX;
            return v->l(x);
        }
        ll res=LL_MAX;
        if(v->l.m!=LL_MAX)
            res=v->l(x);
        int mid=(vl+vr)/2;
        if(x<=mid)
            return min(res,queryMin(v->lft,vl,mid,x));
        else
            return min(res,queryMin(v->rht,mid+1,vr,x));
    }
    ll queryMax(LctElement* v,int vl,int vr,ll x)
    {
        if(v==NULL)
            return -LL_MAX;
        if(vl==vr)
        {
            if(v->l.m==LL_MAX)
                return -LL_MAX;
            return v->l(x);
        }
        ll res=-LL_MAX;
        int mid=(vl+vr)/2;
        if(x<=mid)
            return max(res,queryMax(v->lft,vl,mid,x));
        else
            return max(res,queryMax(v->rht,mid+1,vr,x));
    }
    void freeMemory(LctElement* node)
    {
        if(node==NULL)
            return;
        freeMemory(node->lft);
        freeMemory(node->rht);
        delete node;
    }
public:
    DynamicLCT(bool MinTree=true)
    {
        root=new LctElement();
        minTree=MinTree;
    }
    void update(int vl,int vr,Line nl)
    {
        if(minTree)
            updateMin(root,vl,vr,nl);
        else
            updateMax(root,vl,vr,nl);
    }
    ll query(int vl,int vr,ll x)
    {
        if(minTree)
            return queryMin(root,vl,vr,x);
        else
            return queryMax(root,vl,vr,x);
    }
    ~DynamicLCT()
    {
        freeMemory(root);
    }
};
/*********************************/
