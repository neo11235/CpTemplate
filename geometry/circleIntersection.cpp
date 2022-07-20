#define dis(a,b) sqrtl((a)*(a)+(b)*(b))
const double pi=acosl((long double)-1.0);
template<class T>
long double intersection(pair<T,T> p1,T r1,pair<T,T> p2,T r2)
{
    long double x1,y1,x2,y2,d;
    x1=p1.first;
    y1=p1.second;
    x2=p2.first;
    y2=p2.second;
        d=dis(x1-x2,y1-y2);
    if(r1<r2){
        swap(x1,x2);
        swap(y1,y2);
        swap(r1,r2);
    }
    if((r1+r2)<=d){
        return 0;
    }
    if((d+r2)<=r1){
        return pi*r2*r2;
    }
    long double ar1,ar2,s,ar,th1,th2,tmp;
    s=(r1+r2+d)/2;
    ar=(sqrt(s*(s-r1))*sqrt((s-r2)*(s-d)))*2.0;


    tmp=ar/(d*r1);
    if(tmp>1.0)tmp=1.0;
    th1=asin(tmp);
    ar1=(th1*r1*r1)-(r1*r1*sin(th1*2.0))/2.0;

    tmp=ar/(d*r2);
    if(tmp>1.0)tmp=1.0;
    th2=asin(tmp);
    ar2=(th2*r2*r2)-(r2*r2*sin(th2*2.0))/2.0;

    if((r1*r1-d*d-r2*r2)>0.0)
        ar2=(pi*r2*r2)-ar2;
    ar1+=ar2;
    return ar1;
}
