template<class T>
bool cw(pair<T,T>& a,pair<T,T>&b,pair<T,T>&c){
    return a.xx*(b.yy-c.yy)+b.xx*(c.yy-a.yy)+c.xx*(a.yy-b.yy)<0;
}
template<class T>
bool ccw(pair<T,T>& a,pair<T,T>&b,pair<T,T>&c){
    return a.xx*(b.yy-c.yy)+b.xx*(c.yy-a.yy)+c.xx*(a.yy-b.yy)>0;
}
