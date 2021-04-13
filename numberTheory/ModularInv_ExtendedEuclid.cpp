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
