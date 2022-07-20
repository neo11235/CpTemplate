#define double long double
#define sqr(x) ((x)*(x))
template<class T>
struct pt{
    T x,y;
    pt(T x=0,T y=0):x(x),y(y){}
    pt operator+(const pt& p)const
    {
        return pt{x+p.x,y+p.y};
    }
    pt operator-(const pt& p)const
    {
        return pt{x-p.x,y-p.y};
    }
    pt operator*(const pt& p) const
    {
        return pt{x*p.x-y*p.y,y*p.x+x*p.y};
    }
    T cross(const pt p)const
    {
        return x*p.y-y*p.x;
    }
    T dot(const pt p) const
    {
        return x*p.x+y*p.y;
    }
};
typedef pt<double> point;
const double pres=1e-12;
const double pi=acosl((double)-1.0);
bool ccw(point& a,point&b,point&c){
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y)>=0;
}
double area0(point a,point b)
{
    return abs((a.x*b.y-a.y*b.x)/2.0);
}
double angle(point a,point b)
{
    double d=((a.x*b.x+a.y*b.y))/(sqrtl(a.x*a.x+a.y*a.y)*
                                sqrtl(b.x*b.x+b.y*b.y));

    return acosl(d);
}
double CSI(ll r,point a,point b)
{
    double base=sqrtl((double)sqr(a.x-b.x)+sqr(a.y-b.y));
    double h=abs(a.x*b.y-a.y*b.x)/base;
    if(h<pres)
        return 0;
    double th=angle(a,b);
    point z(0,0);
    int sign=ccw(z,a,b)?1:-1;
    if(h>=r)
    {
        return th*r*r*sign/2.0;
    }
    double za=sqrtl(a.x*a.x+a.y*a.y);
    double zb=sqrtl(b.x*b.x+b.y*b.y);
    if(r*r>=a.x*a.x+a.y*a.y)
    {
        if(r*r>=b.x*b.x+b.y*b.y)
        {
            return (a.x*b.y-a.y*b.x)/2.0;
        }
        else
        {
            double ar=0;
            if((z-a).dot(b-a)>=0)
            {
                if((r*r-h*h)>pres)
                    ar+=sqrtl(r*r-h*h);
                if((za*za-h*h)>pres)
                    ar+=sqrtl(za*za-h*h);
                ar=h*ar/2.0;
            }
            else
            {
                if((r*r-h*h)>pres)
                    ar+=sqrtl(r*r-h*h);
                if((za*za-h*h)>pres)
                    ar-=sqrtl(za*za-h*h);
                ar=h*(ar)/2.0;
            }
            double cc=(2*ar)/h;
            double th2=acosl((za*za+r*r-cc*cc)/(2*za*r));

            ar+=(th-th2)*r*r/2.0;
            return ar*sign;
        }
    }
    else if(r*r>=b.x*b.x+b.y*b.y)
    {
        double ar=0;
        if((z-b).dot(a-b)>=0)
        {
            if((r*r-h*h)>pres)
                ar+=sqrtl(r*r-h*h);
            if((zb*zb-h*h)>pres)
                ar+=sqrtl(zb*zb-h*h);
            ar=h*(ar)/2.0;
        }
        else
        {
            if((r*r-h*h)>pres)
                ar+=sqrtl(r*r-h*h);
            if((zb*zb-h*h)>pres)
                ar-=sqrtl(zb*zb-h*h);
            ar=h*(ar)/2.0;
        }
        double cc=(2*ar)/h;
        double th2=acosl((zb*zb+r*r-cc*cc)/(2*zb*r));
        ar+=(th-th2)*r*r/2.0;
        return ar*sign;
    }
    else
    {
        if((z-a).dot(b-a)<=0||(z-b).dot(a-b)<=0)
        {
            return th*r*r*sign/2.0;
        }
        double ar=0;
        if((r*r-h*h)>pres)
            ar=h*sqrtl(r*r-h*h);
        double th2=2*acosl(h/r);
        ar+=(th-th2)*r*r/2.0;
        return ar*sign;
    }
}
double CTI(ll r,point a,point b,point c)//a b c counterclockwise
{
    return CSI(r,a,b)+CSI(r,b,c)+CSI(r,c,a);
}
double CTI(point k,ll r,point a,point b,point c)
{
    return CTI(r,a-k,b-k,c-k);
}
