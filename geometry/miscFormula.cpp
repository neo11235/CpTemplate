///find the height of a trapezium with length of sides a,b,c,d  a||c
double findH(double a,double b,double c,double d)
{
    const double pres=1e-9;
    double k;
    if(a<c)
        swap(a,c);
    k=a-c;
    if(k<pres)
    {
        if(abs(b-d)>pres)
        {
            return -1;
        }
        return b;
    }
    double csb=(b*b-d*d+k*k)/(2*k*b);//cos(B)
    double h=sqrt(1-csb*csb)*b;
    return h;
}

//checking if 3 point is colinear
bool chkColinear(pll a,pll b,pll c)
{
    return (c.second-a.second)*(b.first-a.first)==(b.second-a.second)*(c.first-a.first);
}
/// polar order
ll cross(pll a,pll b)
{
    return a.first*b.second-a.second*b.first;
}
int quarter(pll a)
{
    if(a.first>=0)
    {
        if(a.second>=0)
            return 0;
        else
            return 3;
    }
    else
    {
        if(a.second>=0)
            return 1;
        return 2;
    }
}
const long double pi=2*acos(0.0);
bool polar_order(pair<pll,int> & a,pair<pll,int>& b)
{
    if(quarter(a.first)==quarter(b.first))
    {
        return cross(a.first,b.first)>0;
    }
    else
        return quarter(a.first)<quarter(b.first);
}
