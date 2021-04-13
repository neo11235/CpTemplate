/**********2d point vector and complex number*********/
//moderately tested

template<class T>
class vector2d{
private:
public:
    T x,y;
    vector2d(){x=y=0;}
    vector2d(T x,T y):x(x),y(y){}
    vector2d operator+(T a){
        return {x+a,y+a};
    }
    vector2d operator+(vector2d v){return {x+v.x,y+v.y};}
    vector2d operator-(){return {-x,-y};}
    vector2d operator-(T a){return{x-a,y-a};}
    vector2d operator-(vector2d v){return {x-v.x,y-v.y};}
    vector2d operator*(T a){return {x*a,y*a};}
    vector2d operator*(vector2d v)//complex multiplication
    {
        return {x*v.x-y*v.y,x*v.y+y*v.x};
    }
    vector2d& operator*=(vector2d v)//complex multiplication
    {
        T tx=x*v.x-y*v.y;
        T ty=x*v.y+y*v.x;
        x=tx;
        y=ty;
        return *this;
    }
    vector2d& operator+=(vector2d v)
    {
        x+=v.x;
        y+=v.y;
        return *this;
    }
    vector2d& operator-=(vector2d v)
    {
        x-=v.x;
        y-=v.y;
        return *this;
    }
    vector2d& operator*=(T a)
    {
        x*=a;
        y*=a;
        return *this;
    }
    vector2d& operator/=(T a)
    {
        x/=a;
        y/=a;
        return *this;
    }
    T abs()
    {
        return sqrt(x*x+y*y);
    }
    T abs2()
    {
        return x*x+y*y;
    }
    vector2d operator/(T a){return {x/a,y/a};}
    vector2d operator/(vector2d v)//complex division
    {
        return ((*this)*vector2d(v.x,-v.y))/v.abs2();
    }
    T dot(vector2d v)
    {
        return x*v.x+y*v.y;
    }
    vector2d<T> rotate(double angle)//counterclockwise rotation
    {
        double cs=cos(angle);
        double sn=sin(angle);
        return {x*cs-y*sn,x*sn+y*cs};
    }
    vector2d<T> rot90()//counterclockwise 90 degree rotation to work with integer points
    {
        return {-y,x};
    }
    T cross(vector2d b)
    {
        return x*b.y-y*b.x;
    }
};

//finds transform such that p1->p3,p2->p4,to find transform of another point r,evaluate a*r+b;
template<class T>
pair<vector2d<T>,vector2d<T> > findLinearTransform(vector2d<T> p1,vector2d<T> p2,vector2d<T> p3,vector2d<T> p4)
{
    vector2d<T> a=(p3-p4)/(p1-p2);
    vector2d<T> b=p3-a*p1;
    return {a,b};
}
template<class T>
T abs(vector2d<T> v)
{
    return sqrt(v.x*v.x+v.y*v.y);
}
template<class T>
T angle(vector2d<T> a,vector2d<T> b)
{
    return acos(a.dot(b)/(abs(a)*abs(b)));
}
template <class T>
ostream& operator<<(ostream& stream,const vector2d<T>& v)
{
    stream<<'('<<v.x<<' '<<v.y<<')';
    return stream;
}
template <class T>
istream& operator>>(istream& stream,vector2d<T>& v)
{
    stream>>v.x>>v.y;
    return stream;
}
/********************************************/


/*****************3d point,vector*****************/
//moderately tested

template<class T>
class vector3d{
public:
    T x,y,z;
    vector3d()
    {
        x=y=z=0;
    }
    vector3d(T a,T b,T c)
    {
        x=a;
        y=b;
        z=c;
    }
    vector3d operator+(T a)
    {
        return vector3d(x+a,y+a,z+a);
    }
    vector3d operator+(vector3d v2)
    {
        return vector3d(x+v2.x,y+v2.y,z+v2.z);
    }
    vector3d operator-(T a)
    {
         return vector3d(x-a,y-a,z-a);
    }
    vector3d operator-(vector3d v2)
    {
        return vector3d(x-v2.x,y-v2.y,z-v2.z);
    }
    T dot(vector3d v2)
    {
        return x*v2.x+y*v2.y+z*v2.z;
    }
    vector3d operator*(T a)
    {
        return vector3d(x*a,y*a,z*a);
    }
    vector3d operator*(vector3d v)//cross product
    {
        return vector3d(y*v.z-z*v.y,-x*v.z+z*v.x,x*v.y-y*v.x);
    }
    vector3d operator/(T d)
    {
        return vector3d(x/d,y/d,z/d);
    }
};
template <class T>
ostream& operator<<(ostream& stream,const vector3d<T>& v)
{
    stream<<'('<<v.x<<' '<<v.y<<' '<<v.z<<')';
    return stream;
}
template <class T>
istream& operator>>(istream& stream,vector3d<T>& v)
{
    stream>>v.x>>v.y>>v.z;
    return stream;
}
template<class T>
T abs(vector3d<T> v)
{
    return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}
