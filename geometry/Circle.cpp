template<class T>
class vector2d{
private:
    vector2d solveSim2Var(T a1,T b1,T c1,T a2,T b2,T c2)
    {

    }
public:
    T x,y;
    vector2d(){x=y=0;}
    vector2d(T x,T y):x(x),y(y){}
    vector2d operator+(T a){
        return {x+a,y+a};
    }
    vector2d operator+(const vector2d& v){return {x+v.x,y+v.y};}
    vector2d operator-(T a){return{x-a,y-a};}
    vector2d operator-(const vector2d& v){return {x-v.x,y-v.y};}
    vector2d operator*(T a){return {x*a,y*a};}
    vector2d operator*(const vector2d& v)//complex multiplication
    {
        return {x*v.x-y*v.y,x*v.y+y*v.x};
    }
    vector2d& operator*=(const vector2d& v)//complex multiplication
    {
        T tx=x*v.x-y*v.y;
        T ty=x*v.y+y*v.x;
        x=tx;
        y=ty;
        return *this;
    }
    vector2d& operator+=(const vector2d& v)
    {
        x+=v.x;
        y+=v.y;
        return *this;
    }
    vector2d& operator-=(const vector2d& v)
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
    vector2d operator/(T a){return {x/a,y/a};}
    vector2d operator/(const vector2d& v)//complex division
    {
        return ((*this)*vector2d(v.x,-v.y))/v.abs();
    }
    T dot(const vector2d& v)
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
    //*** T must be floating point type to use these function
    //to find transformation of any other point evaluate a*x+b
    pair<vector2d,vector2d> findLinearTransform(vector2d& p1,vector2d& p2,\
                                                vector2d& p3,vector2d& p4)
    {
       vector2d a=(p3-p4)/(p1-p2);
       vector2d b=a*p1;
       return {a,b};
    }
};
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

template<class T>
class LineSegment2d{
    const double pres=1e-9;
    bool intersect(T a,T b,T c,T d)
    {
        if(a>b)
            swap(a,b);
        if(c>d)
            swap(c,d);
        return max(a,c)<=min(b,d);
    }
    int sgn(T x)
    {
        return x>=0?x?1:0:-1;
    }
    pair<T,T> findXIntersect(T a,T b,T c,T d)//assuming that they does intersect;
    {
        T x,y;
        if(a>b)
            swap(a,b);
        if(c>d)
            swap(c,d);
        x=max(a,c);
        y=min(b,d);
        return {x,y};
    }
public:
    vector2d<T> p1,p2;
    LineSegment2d(){}
    LineSegment2d(vector2d<T> l1,vector2d<T> l2)
    {
        p1=l1;
        p2=l2;
    }
    //not tested
    bool checkIntersect(LineSegment2d<T> l)// works with T=integer
    {
        if((l.p1-p1).cross(l.p2-p2)==0)
        {
            return intersect(p1.x,p2.x,l.p1.x,l.p2.x);
        }
        else
        {
            return sgn((l.p1-p1).cross(l.p2-p1))!=sgn((l.p1-p2).cross(l.p2-p2))&&
                    sgn((p1-l.p1).cross(p2-l.p1))!=sgn((p1-l.p2).cross(p2-l.p2));
        }
    }
    bool checkParallel(LineSegment2d<T> l)
    {
        return abs((p2-p1).cross(l.p2-p1))<pres;//check for overflow
    }
    T evaluate(T x)//evaluate y at x of the line this segment is part of
    {
        return p1.y+(x-p1.x)*(p2.y-p1.y)/(p2.x-p1.x);
    }
    //not tested
    bool interSection(LineSegment2d<T> l,LineSegment2d<T>& out)//designed for T=floating point numbers
    {
        if(!(intersect(p1.x,p2.x,l.p1.x,l.p2.x)&&intersect(p1.y,p2.y,l.p1.y,l.p2.y)))
            return false;
        if(checkParallel(l))
        {
            pair<T,T> tmp=findXIntersect(p1.x,p2.x,l.p1.x,l.p2.x);
            out.p1.x=tmp.first;
            out.p1.y=evaluate(tmp.first);
            out.p2.x=tmp.second;
            out.p2.y=evaluate(tmp.second);
            return true;
        }
        vector2d<T> B,D;
        B=p2-p1;
        D=l.p2-l.p1;
        vector2d<T> rval=p1+B*((l.p1.cross(D)-p1.cross(D))/(B.cross(D)));
        out.p1=rval;
        out.p2=rval;
        return true;
    }
};
template<class T>
class LineEq{//line in equation form
public:
    T a,b,c;//ax+by+c=0;
    LineEq(T a,T b,T c){this->a=a;this->b=b;this->c=c;}
    T evaluate(T x){return (c-a*x)/b;}

    //T should be double or long double
    void normalize()
    {
        T d=sqrt(a*a+b*b);
        a/=d;
        b/=d;
        c/=d;
    }
    T norm()
    {
        return sqrt(a*a+b*b);
    }


};
template<class T>
class Circle{
    const double pres=1e-9;
    const double pi=2*acos(0.0);
public:
    vector2d<T> center;
    T radius;
    Circle(){}
    Circle(vector2d<T> center,T radius){this->center=center;this->radius=radius;}

    bool checkInterSection(LineEq<T> line)
    {
        return abs(line.a*center.x+line.b*center.y+line.c)/line.norm()<=radius;
    }
    int interSection(LineEq<T> line,LineSegment2d<T>& out)
    {
        line.c+=line.a*center.x+line.b*center.y;
        line.normalize();
        vector2d<T> nrm(-line.a*line.c,-line.b*line.c);
        T d=abs(line.c);
        if(d<pres)
        {
            nrm.x=-line.a;
            nrm.y=-line.b;
            nrm=nrm.rot90();
            out.p1=nrm*radius;
            out.p2=nrm*-radius;
            return 2;
        }
        nrm/=d;
        if(d>radius)
            return 0;
        if(abs(d-radius)<pres)//touch the circle
        {
            out.p1=center+nrm*radius;
            return 1;
        }
        vector2d<T> r=nrm.rot90();
        T d2=sqrt(radius*radius-d*d);
        out.p1=center+nrm*d+r*d2;
        out.p2=center+nrm*d-r*d2;
        return 2;
    }
    bool interSection(LineEq<T> line,pair<T,T>& angularout)//find angular intersection,angle is measured with respect to +x axis
    {
        line.c+=line.a*center.x+line.b*center.y;
        line.normalize();
        vector2d<T> nrm(-line.a*line.c,-line.b*line.c);
        T d=abs(line.c);
        if(d>pres)
            nrm/=abs(line.c);
        else
        {
            nrm.x=line.a;
            nrm.y=line.b;
        }
        if(d>radius)
            return false;
        T d2=sqrt(radius*radius-d*d);
        if(d<pres){
            angularout.second=pi/2;
        }
        else
            angularout.second=atan(d2/d);
        angularout.first=-angularout.second;
        T ang=angle(vector2d<T>((T)1,(T)0),nrm);
        if(nrm.y<0)
        {
            ang=2*pi-ang;
        }
        angularout.first+=ang;
        angularout.second+=ang;
        return true;
    }
    int interSection(Circle<T> c2,LineSegment2d<T>& out)
    {
        LineEq<T> line(2*(c2.center.x-center.x),2*(c2.center.y-center.y),center.x*center.x+center.y*center.y-radius*radius\
                         -c2.center.x*c2.center.x-c2.center.y*c2.center.y+c2.radius*c2.radius);
        return interSection(line,out);
    }
    bool interSection(Circle<T> c2,pair<T,T>& angularout)
    {
        LineEq<T> line(2*(c2.center.x-center.x),2*(c2.center.y-center.y),center.x*center.x+center.y*center.y-radius*radius\
                         -c2.center.x*c2.center.x-c2.center.y*c2.center.y+c2.radius*c2.radius);
        return interSection(line,angularout);
    }
};
