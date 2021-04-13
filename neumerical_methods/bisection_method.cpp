double f(double x){
    //evaluate x
}
double find_root(double l,double r){
    double mid;
    double fl=f(l),fr=(r),fmid,mlt;
    while((r-l)>pres){
        mid=(l+r)/2;
        fmid=f(mid);
        if(fl>0.0){
            if(fmid>=0.0){
                fl=fmid;
                l=mid;
            }
            else{
                fr=fmid;
                r=mid;
            }
        }
        else{
            if(fmid>=0.0){
                fr=fmid;
                r=mid;
            }
            else{
                fl=fmid;
                l=mid;
            }
        }
    }
    return l;
}
