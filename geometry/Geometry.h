#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED
/*****structure****/
template<class T> class point{
public:
    T x,y;
    point(){
        x=y=(T)0;
    }
    point(T a,T b){
        x=a;
        y=b;
    }
    bool operator<(const point<T>&);
    void operator=(const point<T>&);//i have some problem with the this pointer,some error occurs when returning *this object
};
template<class T>bool point<T>::operator<(const point<T>& p1){
    return x<p1.x||(x==p1.x&&y<p1.y);
}
template<class T>void point<T>::operator=(const point<T>& p1){
    x=p1.x;
    y=p1.y;
}
/****algorithm***/
template<class T> T polygon_area(T* X,T* Y,int n){//returns 2*signed area
    int i;
    T ans=(T)0;
    for(i=0;i<n;i++){
        ans+=X[i]*Y[(i+1)%n];
        ans-=Y[i]*X[(i+1)%n];
    }
    return ans;
}
/**********convex Hull***********/
#ifndef xx
#define xx first
#endif // xx
#ifndef yy
#define yy second
#endif // yy
template<class T>
bool cw(pair<T,T>& a,pair<T,T>&b,pair<T,T>&c){
    return a.xx*(b.yy-c.yy)+b.xx*(c.yy-a.yy)+c.xx*(a.yy-b.yy)<0;
}
template<class T>
bool ccw(pair<T,T>& a,pair<T,T>&b,pair<T,T>&c){
    return a.xx*(b.yy-c.yy)+b.xx*(c.yy-a.yy)+c.xx*(a.yy-b.yy)>0;
}
template<class T>
void convex_hull(vector<pair<T,T> >&a){//O(n) a is assumed to be sorted
    if(a.size()<2)return;
    pair<T,T> p1,p2;
    vector<pair<T,T> > up,down;
    p1=a[0];
    p2=a.back();
    up.push_back(p1);
    down.push_back(p1);
    for(int i=1;i<(int)a.size();i++){
        if(i==a.size()-1||cw(p1,a[i],p2)){
            while(up.size()>=2&&!cw(up[up.size()-2],up[up.size()-1],a[i]))up.pop_back();
            up.push_back(a[i]);
        }
        if(i==a.size()-1||ccw(p1,a[i],p2)){
            while(down.size()>=2&&!ccw(down[down.size()-2],down[down.size()-1],a[i]))down.pop_back();
            down.push_back(a[i]);
        }
    }
    a.clear();
    for(int i=0;i<(int)up.size();i++)
        a.push_back(up[i]);
    for(int i=down.size()-2;i>0;i--)
        a.push_back(down[i]);
    return;
}
double dis(double x,double y){
    return sqrt(x*x+y*y);
}
double angle(double x1,double y1,double x2,double y2){
    return acos((x1*x2+y1*y2)/(dis(x1,y1)*dis(x2,y2)));
}





#endif // GEOMETRY_H_INCLUDED
