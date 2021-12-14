ll pal(int len)
{
    len=(len+1)/2;
    ll ans=9;
    for(int i=1;i<len;++i)
        ans*=10;
    return ans;
}
ll PalBelow_a(ll a)//from 0 to a inclusive
{
    if(a<10)
        return a+1;
    vi b;
    ll ta=a;
    while(ta>0)
    {
        b.push_back(ta%10);
        ta/=10;
    }
    reverse(b.begin(),b.end());
    int len=(int)b.size();
    ll ans=0;
    for(int i=1;i<len;++i)
    {
        ans+=pal(i);
    }
    int l2=(len+1)/2;
    ll x=1,y=b[0];
    for(int i=1;i<l2;++i)
    {
        x*=10;
        y*=10;
        y+=b[i];
    }
    ans+=(y-x);
    for(int i=l2;i<len;++i)
    {
        y*=10;
        y+=b[len-1-i];
    }
    if(y<=a)
        ++ans;
    return ans+1;
}
