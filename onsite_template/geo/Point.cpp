template<class T>
struct Point{
    T x , y;
    Point(){x=y=0;}
    Point(T x,T y):x(x),y(y){}
    Point operator+(Point v){return {x+v.x,y+v.y};}
    Point operator-(Point v){return {x-v.x,y-v.y};}
    Point operator*(Point v){
        return {x*v.x-y*v.y,x*v.y+y*v.x};}
    Point operator*(T a){
        return {x*a,y*a};}
    Point operator/(T v){
        return {x/v,y/v};}
    T norm(){
        return sqrt(x*x+y*y);}
    T norms(){
        return x*x+y*y;}
    Point operator/(Point v){
        return ((*this)*Point(v.x,-v.y))/v.norms();}
    T dot(Point v){
        return x*v.x+y*v.y;}
    T cross(Point b){
        return x*b.y-y*b.x;}
};
template <class T>
istream& operator>>(istream& stream,Point<T>& v)
{
    stream>>v.x>>v.y;
    return stream;
}
