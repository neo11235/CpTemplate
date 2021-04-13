#include <bits/stdc++.h>
using namespace std;
#define sci1(a) scanf("%d",&a)
#define sci2(a,b) scanf("%d %d",&a,&b)
#define sci3(a,b,c) scanf("%d %d %d",&a,&b,&c)
#define scs(s) scanf("%s",s)
#ifndef GET_MACRO
#define GET_MACRO(__1,__2,__3,NAME,...) NAME
#endif // GET_MACRO
#define sci(...) GET_MACRO(__VA_ARGS__,sci3,sci2,sci1)(__VA_ARGS__)
#define ll long long
#define pii pair<int,int>
#define mp(a,b) make_pair(a,b)
#define LSB(i) ((i)&-(i))
#define read freopen("input.txt","r",stdin)
#define write freopen("output.txt","w",stdout)
#define infl 0x7fffffffffffffff
#define infi 0x7fffffff
#define pb push_back
#define xx first
#define yy second
bool check_sign(pii p1,pii p2,pii p3){
    return (1ll*p1.first*p2.second+1ll*p2.first*p3.second+1ll*p3.first*p1.second
            -1ll*p1.second*p2.first-1ll*p2.second*p3.first-1ll*p3.second*p1.first)>=0ll;
}
//points must be given in anticlockwise order
bool check_if_inside_polygon(vector<pii>& points,pii qpoint){
    int n=points.size();
    int l=1;
    int r=n-1;
    int mid;
    bool sign=check_sign(points[0],points[1],qpoint);
    if(!sign){
        return false;
    }
    while(l<r){
        mid=(l+r)/2;
        sign=check_sign(points[0],points[mid],qpoint);
        if(sign)
            l=mid+1;
        else
            r=mid-1;
        }
    if(check_sign(points[0],points[l],qpoint))
        l++;
    if(l==n)
        l--;
    sign=check_sign(points[l-1],points[l],qpoint)&&
            check_sign(points[0],points[l-1],qpoint)&&
            check_sign(points[l],points[0],qpoint);
    return sign;
}
/*****************************better implementation*************/
template<class T>
T check_sign(vector2d<T> p1,vector2d<T> p2,vector2d<T> p3){
    return (p1.x*p2.y+p2.x*p3.y+p3.x*p1.y
            -p1.y*p2.x-p2.y*p3.x-p3.y*p1.x);
}

template<class T>
ll check_sign(pair<T,T> p1,pair<T,T> p2,pair<T,T> p3){
    return (1ll*p1.first*p2.second+1ll*p2.first*p3.second+1ll*p3.first*p1.second
            -1ll*p1.second*p2.first-1ll*p2.second*p3.first-1ll*p3.second*p1.first);
}
//points must be given in anticlockwise order
template<class T>
bool check_if_inside_polygon(vector<pair<T,T>>& points,pair<T,T> qpoint){
    int n=points.size();

    if(check_sign(points[0],points[1],qpoint)<0)
        return false;
    int l=1,r=n-1;
    while(r>l+1)
    {
        int mid=(l+r)/2;
        if(check_sign(points[0],points[mid],qpoint)>=0)
            l=mid;
        else
            r=mid;
    }
    if(check_sign(points[0],points[r],qpoint)>0||check_sign(points[l],points[r],qpoint)<0)
        return false;
    /// add these line if u want strictly inside
//    if(l==1&&check_sign(points[0],points[1],qpoint)==0)
//        return false;
//    if(r==n-1&&check_sign(points[0],points[r],qpoint)==0)
//        return false;
//    if(check_sign(points[l],points[r],qpoint)==0)
//        return false;
    return true;
}
