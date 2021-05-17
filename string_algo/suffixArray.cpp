/****emaxx implementation***********/
vector<int> sortCyclicShifts(string const& s)
{
    int n=s.size();
    const int alphabet=256;
    vector<int> p(n),c(2*n),cnt(max(alphabet,n),0);
    for(int i=0;i<n;i++)
        cnt[s[i]]++;
    for(int i=1;i<alphabet;i++)
        cnt[i]+=cnt[i-1];
    for(int i=0;i<n;i++)
        p[--cnt[s[i]]]=i;
    c[p[0]]=0;
    int classes=1;
    for(int i=1;i<n;i++)
    {
        if(s[p[i]]!=s[p[i-1]])
            classes++;
        c[p[i]]=classes-1;
    }
    for(int i=n;i<2*n;i++)
    {
        c[i]=c[i-n];
    }
    vector<int> pn(n),cn(2*n);
    for(int h=0;(1<<h)<n;h++)
    {
        for(int i=0;i<n;i++)
        {
            pn[i]=p[i]-(1<<h);
            if(pn[i]<0)
                pn[i]+=n;
        }
        fill(cnt.begin(),cnt.begin()+classes,0);
        for(int i=0;i<n;i++)
            cnt[c[pn[i]]]++;
        for(int i=1;i<classes;i++)
            cnt[i]+=cnt[i-1];
        for(int i=n-1;i>=0;i--)
            p[--cnt[c[pn[i]]]]=pn[i];
        cn[p[0]]=0;
        classes=1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) ]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) ]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        if(classes==n)
            return p;
        for(int i=n;i<2*n;i++)
        {
            cn[i]=cn[i-n];
        }
        c.swap(cn);
    }
    return p;
}
vector<int> suffix_array_construction(string s) {
    s += "$";
    vector<int> sorted_shifts = sortCyclicShifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}
/**************************************************/
