template <class T>pair<T,T> extended_euclid(T n,T m){//returns <u,v> such that nu+mv=(n,m)
    T rn_1,rn,sn_1,sn,tn_1,tn,tr,ts,tt,q;
    rn_1=n;sn_1=1;tn_1=0;
    rn=m;sn=0;tn=1;
    while(1){
        tr=rn_1%rn;
        q=(rn_1-tr)/rn;
        ts=sn_1-(q*sn);
        tt=tn_1-(q*tn);
        if(tr==0){
            return mp(sn,tn);
        }
        sn_1=sn;sn=ts;
        tn_1=tn;tn=tt;
        rn_1=rn;rn=tr;
    }
}
///asuming the line equation in form ax+by=c
///assuming at least one of a or b is not zero,check it before passing to this function
ll shiftx(ll x,ll refx,ll q)
{
    if(x==refx)
        return x;
    if(x<refx)
    {
        ll d=refx-x;
        if(d%q)
        {
            d=d-d%q+q;
        }
        return x+d;

    }
    else
    {
        ll d=x-refx;
        if(d%q)
            d-=d%q;
        return x-d;
    }
}
ll solveDiophantine(ll a,ll b,ll c,ll x1,ll x2,ll y1,ll y2)
{
    if(a==0)
    {
        if(abs(c)%abs(b))
            return 0;
        ll y=c/b;
        if(y>=y1&&y<=y2)
            return (x2-x1+1);
        return 0;
    }
    if(b==0)
    {
        if(abs(c)%abs(a))
            return 0;
        ll x=c/a;
        if(x>=x1&&x<=x2)
            return (y2-y1+1);
        return 0;
    }
    ll g=__gcd(abs(a),abs(b));
    if(abs(c)%g)
    {
        return 0;
    }
    pair<ll,ll> sol=extended_euclid(abs(a),abs(b));
    if(a<0)
    {
        a=-a;
        b=-b;
        c=-c;
    }
    if(b<0)
    {
        sol.second=-sol.second;
    }
    sol.first*=(c/g);
    sol.second*=(c/g);
    ll x1p,x2p;
    if(b<0)//slope is positive
    {
        x1p=floor(1.0*(c-b*y1)/a);
        if((c-b*y1)%a!=0)
            x1p++;
        x2p=floor(1.0*(c-b*y2)/a);
    }
    else//slope is negative
    {
        x2p=floor(1.0*(c-b*y1)/a);
        x1p=floor(1.0*(c-b*y2)/a);
        if((c-b*y2)%a!=0)
            x1p++;
    }
    ll x11,x22;
    x11=max(x1,x1p);
    x22=min(x2,x2p);
    if(x22<x11)
        return 0;
    ll lx,rx;
    lx=shiftx(sol.first,x11,abs(b/g));
    rx=shiftx(sol.first,x22,abs(b/g));
    if(rx!=x22)
    {
        rx-=abs(b/g);
    }
    return max((rx-lx)/(abs(b/g))+1,0ll);
}
void solvecases(int cse)
{
    ll a,b,c,x1,x2,y1,y2;
    cin>>a>>b>>c>>x1>>x2>>y1>>y2;

    ll sol;
    if(a==0&&b==0)
    {
        if(c==0)
            sol=(x2-x1+1)*(y2-y1+1);
        else
            sol=0;
    }
    else
    {
        sol=solveDiophantine(a,b,-c,x1,x2,y1,y2);
    }
    cout<<"Case "<<cse<<": "<<sol<<'\n';

}
