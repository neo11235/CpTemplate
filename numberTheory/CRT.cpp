template <class T>
pair<T,T> extended_euclid(T n,T m){//returns <u,v> such that nu+mv=(n,m)
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
ll basicCRT(vector<ll>& a,vector<ll>& num)
{
    ll N=1;
    for(auto e:num)
        N*=e;
    int n=(int)num.size();
    ll x=0;
    for(int i=0;i<n;i++)
    {
        ll Ni=N/num[i];
        pll tmp=extended_euclid(Ni,num[i]);
        x+=(((a[i]*Ni)%N)*tmp.first)%N;
        x%=N;
        x+=N;
        x%=N;
    }
    return x;
}


///********************************garner**************************
template <class T>T n_inverse_mod_m(T n,T m){
    T rn_1,rn,sn_1,sn,tn_1,tn,tr,ts,tt,q;
    rn_1=n;sn_1=1;tn_1=0;
    rn=m;sn=0;tn=1;
    while(1){
        tr=rn_1%rn;
        q=(rn_1-tr)/rn;
        ts=sn_1-(q*sn);
        tt=tn_1-(q*tn);
        if(tr==0){
            return (sn+m)%m;
        }
        sn_1=sn;sn=ts;
        tn_1=tn;tn=tt;
        rn_1=rn;rn=tr;
    }
}
void garner(vector<ll>& a,vector<ll> & p,vector<ll>& out){
    int n=(int)p.size();
    for(int i=0;i<n;i++)
    {
        out[i]=a[i];
        for(int j=0;j<i;j++)
        {
            out[i]=(out[i]-out[j])*n_inverse_mod_m(p[j],p[i]);
            out[i]%=p[i];
            if(out[i]<0)
                out[i]+=p[i];
        }
    }
}
ll garnerCRT(vector<ll>&a,vector<ll>& p)
{
    vector<ll> out(p.size());
    garner(a,p,out);
    ll N=1;
    for(auto e:p)
        N*=e;
    ll cur=out[0];
    ll N1=1;
    int n=p.size();
    for(int i=1;i<n;i++)
    {
        N1*=p[i-1];
        cur+=(out[i]*N1)%N;
        cur%=N;
    }
    return cur;
}
