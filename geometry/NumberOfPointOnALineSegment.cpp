template <class T>
T npoint(pair<T,T> l,pair<T,T> r)//inclusive
{
    T x=abs(l.first-r.first);
    T y=abs(l.second-r.second);
    if(x==0)
    {
        return y+1;
    }
    else if(y==0)
    {
        return x+1;
    }
    T g=__gcd(x,y);
    return (x/g)+1;
}
