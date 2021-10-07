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

/**
monotone slope and arbitrary point query
runtime:    insert() O(1) average
            query() log(n)
**/
struct Line{
    long long m,c;//mx+c
    Line(){
        m=c=infl;
    }
    Line(ll m,ll c):m(m),c(c){}
    long long operator()(long long x)
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
        x=(long double)(l.c-c)/(m-l.m);
        y=(long double)m*x+c;
        return {x,y};
    }
};
//cht with increasing order of slope
//query in arbitrary order
//querying for maximum
//no parallel line
struct CHT{
    deque<Line> Q;
    void insert(Line nl)
    {
        while(Q.size()>1&&Q.back().intersect(nl)<Q[Q.size()-2].intersect(nl))
            Q.pop_back();
        Q.push_back(nl);
    }
    ll query(ll x)
    {
        if(Q.size()==1)
            return Q[0](x);
        if(Q[0].intersect(Q[1]).first>=x)
        {
            return Q[0](x);
        }
        int l=1,r=(int)Q.size()-1;
        while(r>l+1)
        {
            int mid=(l+r)/2;
            if(Q[mid].intersect(Q[mid-1]).first<x)
                l=mid;
            else
                r=mid;
        }
        return max(Q[l](x),Q[r](x));

    }
    void clear()
    {
        Q.clear();
    }
};
//decreasing order of slope
struct CHT2{
    deque<Line> Q;
    void insert(Line nl)
    {
        while(Q.size()>1&&Q[0].intersect(nl)>Q[1].intersect(nl))
            Q.pop_front();
        Q.push_front(nl);
    }
    ll query(ll x)
    {
        if(Q.size()==1)
            return Q[0](x);
        if(Q[0].intersect(Q[1]).first>=x)
        {
            return Q[0](x);
        }
        int l=1,r=(int)Q.size()-1;
        while(r>l+1)
        {
            int mid=(l+r)/2;
            if(Q[mid].intersect(Q[mid-1]).first<x)
                l=mid;
            else
                r=mid;
        }
        return max(Q[l](x),Q[r](x));

    }
    void clear()
    {
        Q.clear();
    }
};
/*****************************************/
/**
Fully Generalized implementation for Monotone slope,Arbitrary query
runtime insert() O(1)
        query() O(logn)
**/
class MonotoneCHT{
    deque<Line> Q;
    int type;
    void insertBack(Line nl)
    {
        //handle parallel line insertion,there cannot be more than one parallel line to new line currently inside Q;
        if(!Q.empty()&&Q.back().parallel(nl))
        {
            if(type<2)
            {
                if(Q.back().c>nl.c)
                    Q.pop_back();
                else
                    return;
            }
            else
            {
                if(Q.back().c<nl.c)
                    Q.pop_back();
                else
                    return;
            }
        }
        while(Q.size()>1&&Q.back().intersect(nl)<Q[Q.size()-2].intersect(nl))
            Q.pop_back();
        Q.push_back(nl);
    }
    void insertFront(Line nl)
    {
        //handle parallel line insertion,there cannot be more than one parallel line to new line currently inside Q;
        if(!Q.empty()&&Q[0].parallel(nl))
        {
            if(type<2)
            {
                if(Q[0].c>nl.c)
                    Q.pop_front();
                else
                    return;
            }
            else
            {
                if(Q[0].c<nl.c)
                    Q.pop_front();
                else
                    return;
            }
        }
        while(Q.size()>1&&Q[0].intersect(nl)>Q[1].intersect(nl))
            Q.pop_front();
        Q.push_front(nl);
    }
    pii bSearch(ll x)
    {
        if(Q.size()==1||Q[0].intersect(Q[1]).first>=x)
            return {0,0};
        int l=1,r=(int)Q.size()-1;
        while(r>l+1)
        {
            int mid=(l+r)/2;
            if(Q[mid].intersect(Q[mid-1]).first<x)
                l=mid;
            else
                r=mid;
        }
        return {l,r};
    }
public:
    //slope increasing or decreasing(not query point,query point is arbitrary),querying for maximum or minimum
    MonotoneCHT(bool increasing,bool maximum)
    {
        type=increasing;
        if(maximum)
            type|=2;
    }
    void insert(Line nl)
    {
        if(type==3||type==0)
            insertBack(nl);
        else
            insertFront(nl);
    }
    ll fastQuery(ll x)//if monotone query satisfied //not tested,although it should be ok
    {
        #ifdef INCREASING_QUERY
        while(Q.size()>1&&Q[0].intersect(Q[1]).first<x)
            Q.pop_front();
        return Q[0](x);
        #else
        while(Q.size()>1&&Q.back().intersect(Q[(int)Q.size()-2]).first>x)
            Q.pop_back();
        return Q.back()(x);
        #endif
    }
    ll query(ll x)
    {
        pii indx=bSearch(x);
        if(type<2)
            return min(Q[indx.first](x),Q[indx.second](x));
        return max(Q[indx.first](x),Q[indx.second](x));
    }
    void clear()
    {
        Q.clear();
    }
};
/***********************************************/

/***********set based implementation
source:https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h

***************************/
struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

/*********************************************/
