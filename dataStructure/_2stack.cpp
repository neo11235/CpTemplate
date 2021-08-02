/******first implementation*************/
struct stack{
    vector<ll> s,g={0ll};
    void push(ll x)
    {
        s.push_back(x);
        g.push_back(__gcd(x,g.back()));
    }
    ll pop()
    {
        ll res=s.back();
        s.pop_back();
        g.pop_back();
        return res;
    }
    ll gcd()
    {
        return g.back();
    }
    bool empty()
    {
        return s.empty();
    }

};
::stack s1,s2;
void add(ll x)
{
    s2.push(x);
}
void remove()
{
    if(s1.empty())
    {
        while(!s2.empty())
            s1.push(s2.pop());
    }
    s1.pop();
}
ll gcd()
{
    return __gcd(s1.gcd(),s2.gcd());
}
void clear()
{
    while(!s1.empty())
        s1.pop();
    while(!s2.empty())
        s2.pop();
}
/*************************************/
