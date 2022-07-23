///first implementation
vector<ll> FWHT(vector<ll> P, bool inverse) {
    int n=P.size();
    assert((n&(n-1))==0);
    for (int len = 1; 2 * len <= n; len <<= 1) {
        for (int i = 0; i < n; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                ll u = P[i + j];
                ll v = P[i + len + j];
                P[i + j] = u + v;
                P[i + len + j] = u - v;
            }
        }
    }

    if (inverse) {
        for (int i = 0; i < n; i++)
            P[i] = P[i] / n;
    }

    return P;
}
vector<ll> xorConvo(vector<ll> a,vector<ll> b)
{
    int n=a.size();
    assert(!(n&(n-1)));
    a=FWHT(a);
    b=FWHT(b);
    for(int i=0;i<n;++i)
    {
        a[i]*=b[i];
    }
    return FWHT(a,true);
}
