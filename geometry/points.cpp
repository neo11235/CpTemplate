#include <bits/stdc++.h>
using namespace std;
template <class T>
class Point{
public:
    int  x,y;
    Point(){x=0;y=0;}
    Point(T a,T b){x=a;y=b;}



};
template <class T>
ostream& operator<<(ostream& os,const Point<T> p){
        return os<<'('<<p.x<<','<<p.y<<')';
}
int main(){
    Point<int> p(2,3);
    cout<<p<<endl;
}
