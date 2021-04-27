//implementation for:
//lines are sorted by decreasing slopes order
//query are sorted by decreasing x
//this is the implementation to solve https://codeforces.com/contest/1083/problem/E
struct Line{
    long long m,c;//mx+c
    long long eval(long long x)
    {
        return m*x+c;
    }
    bool parallel(Line l)
    {
        return m==l.m;
    }
    pair<long double,long double> intersect(Line l)//assuming not parallel
    {
        long double x,y;
        x=(l.c-c)/(m-l.m);
        y=m*x+c;
        return {x,y};
    }
};
ll solve(vector<tuple<ll,ll,ll> >& rec)
{
    sort(rec.begin(),rec.end());
    deque<Line> dq;
    dq.push_front({0,0});
    ll ans=0;
    int n=rec.size();
    for(auto e:rec)
    {
        ll p,q,r;
        tie(p,q,r)=e;
        while(dq.size()>1&&dq.back().eval(q)<=dq[dq.size()-2].eval(q))
            dq.pop_back();
        ll cl=dq.back().eval(q)+p*q-r;
        Line nl={-p,cl};
        if(cl>ans)
        {
            while(dq.size()>1&&dq[0].intersect(dq[1])<=dq[0].intersect(nl))
                dq.pop_front();
            dq.push_front(nl);
            ans=cl;
        }
    }
    return ans;
}
int main()
{
    ll n,p,q,a;
    vector<tuple<ll,ll,ll> > rec;
    cin>>n;
    while(n--)
    {
        cin>>p>>q>>a;
        rec.emplace_back(p,q,a);
    }
    cout<<solve(rec)<<endl;
}


/****Generalized implementation****/

