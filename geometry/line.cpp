
//t should be floating point type
template<class T>
class Line{
public:
    T m,c;//y=mx+c

};
template<class T>
class LineEq{//line in equation form 2d
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
class Line{///2d line,p1 and p2 are 2 distinct point on the line
    const double pres=1e-9;
public:
    vector2d<T> p1,p2;//p1 p2 must be distinct
    Line(vector2d<T> p1,vector2d<T> p2)
    {
        this->p1=p1;
        this->p2=p2;
    }
    T val(T x)
    {
        return p1.y+(x-p1.x)*(p2.y-p1.y)/(p2.x-p1.x);
    }

    bool checkParallel(Line l)
    {
        return abs((p2-p1).cross(l.p2-l.p1))<pres;
    }
    vector2d<T> interSection(Line l)
    {
        vector2d<T> B,D;
        B=p2-p1;
        D=l.p2-l.p1;
        vector2d<T> rval=p1+B*((l.p1.cross(D)-p1.cross(D))/(B.cross(D)));
        return rval;
    }
};
template<class T>
class Line3d{
    double pres=1e-9;
public:
    vector3d<T> p,u;//L(t)=p+ut
    Line3d(vector3d<T> p,vector3d<T> u):p(p),u(u){}
    vector3d<T> evaluate(T t)
    {
        return p+u*t;
    }
    T minDistance(Line3d<T> L)///not tested,should work for any dimension
    {
        T a,b,c,d,e,s,t;
        vector3d<T> w=p-L.p;
        a=u.dot(u);
        b=u.dot(L.u);
        c=L.u.dot(L.u);
        d=u.dot(w);
        e=L.u.dot(w);
        if(abs(a*c-b*b)<pres)
        {
            s=0;
            t=d/b;
        }
        else
        {
            s=(b*e-d*c)/(a*c-b*b);
            t=(a*e-b*d)/(a*c-b*b);
        }
        w=w+u*s-L.u*t;
        return abs(w);
    }
};


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
    T minDistance(vector2d<T> p)
    {
        T d=min(abs(p-p1),abs(p-p2));
        if((p2-p1).dot(p-p1)>=0&&(p1-p2).dot(p-p2)>=0)
        {
            d=min(d,((p2-p1).cross(p-p1))/abs(p2-p1));
        }
        return d;
    }
};
const long double pres=1e-11;
template<class T>
class lineSegment3d{
public:
    //T should be floating point type
    vector3d<T> p,u;//linesegment [p,p+u]
    lineSegment3d(){}
    lineSegment3d(vector3d<T> pts,vector3d<T> dir)
    {
        p=pts;
        u=dir;
    }
    void set(vector3d<T> pts,vector3d<T> dir)
    {
        p=pts;
        u=dir;
    }
    T minDistance(vector3d<T> qp)//minimum distance from point to lineSegment
    {
        long double d=min(abs(p-qp),abs(p+u-qp));
        if((qp-p).dot(u)>=0&&(qp-p-u).dot(u)<=0)
        {
            d=min(d,abs(u*(qp-p))/abs(u));
        }
        return d;
    }
    T minDistance(lineSegment3d<T> L)
    {
        T a,b,c,d,e,s,t;
        vector3d<T> w=p-L.p;
        a=u.dot(u);
        b=u.dot(L.u);
        c=L.u.dot(L.u);
        d=u.dot(w);
        e=L.u.dot(w);
        if(abs(a*c-b*b)<pres)
        {
            s=0;
            t=d/b;
        }
        else
        {
            s=(b*e-d*c)/(a*c-b*b);
            t=(a*e-b*d)/(a*c-b*b);
        }
        if(s>=-pres&&s<=1.0+pres&&t>=-pres&&t<=1.0+pres)
        {
            w=w+u*s-L.u*t;
            return abs(w);
        }
        T dmin=min(minDistance(L.p),minDistance(L.p+L.u));
        dmin=min(dmin,min(L.minDistance(p),L.minDistance(p+u)));
        return dmin;
    }

};
