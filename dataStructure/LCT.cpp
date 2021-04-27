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
