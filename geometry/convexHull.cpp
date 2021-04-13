/**********convex Hull (no boundary points)***********/
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
