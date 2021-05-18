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

/*****************class based implementation***********/
class SuffixArray{
    string s,original;
    int n,originalLen;
    const int alphabet=256;
    vector<int> suffArray;
    vector<int> lcp;
    vector<int> pos;
    #define LOG_N 20
    #define MAXN 1000000
    //int sparseTable[LOG_N][MAXN];
    int* sparseTable[LOG_N];
    void sortCyclicShifts()
    {
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
            for (int i=1;i<n;i++) {
                pair<int,int> cur={c[p[i]],c[(p[i]+(1<<h))]};
                pair<int,int> prev={c[p[i-1]],c[(p[i-1]+(1<<h))]};
                if (cur != prev)
                    ++classes;
                cn[p[i]] = classes - 1;
            }
            if(classes==n)
                break;
            for(int i=n;i<2*n;i++)
            {
                cn[i]=cn[i-n];
            }
            c.swap(cn);
        }
        suffArray=p;
    }
    void calculateLcpArray()
    {
        pos.resize(n);
        lcp.resize(n);
        for(int i=0;i<n;i++)
        {
            pos[suffArray[i]]=i;
        }
        int k=0;
        for(int i=0;i<n-1;i++)
        {
            int indx=pos[i];
            int j=suffArray[indx-1];
            while(s[i+k]==s[j+k])
            {
                k++;
            }
            lcp[indx-1]=k;
            if(k)
                k--;
        }
    }
    void buildSparseTable()
    {
        for(int i=0;i<n;i++)
        {
            sparseTable[0][i]=lcp[i];
        }
        int h=1;
        for(int j=1;j<LOG_N;j++)
        {
            int i;
            for(i=0;i+h<n;i++)
            {
                sparseTable[j][i]=min(sparseTable[j-1][i],sparseTable[j-1][i+h]);
            }
            for(;i<n;i++)
            {
                sparseTable[j][i]=sparseTable[j-1][i];
            }
            h=h<<1;
        }
    }
public:
    SuffixArray(const string& s,bool buildlcp=true)
    {
        this->original=s;
        this->s=original+'$';
        n=s.size()+1;
        originalLen=n-1;
        sortCyclicShifts();
        memset(sparseTable,0,sizeof(sparseTable));
        if(buildlcp)
        {
            for(int i=0;i<LOG_N;i++)
            {
                sparseTable[i]=new int[MAXN];
            }
            buildLcp();
        }
    }
    vector<int> getSuffixArray()
    {
        return suffArray;
    }
    vector<int> getLcp()
    {
        return lcp;
    }
    void buildLcp()
    {
        calculateLcpArray();
        buildSparseTable();
    }
    int lcpQuery(int i,int j)
    {
        if(i==j)
            return originalLen-i;
        int posi=pos[i];
        int posj=pos[j];
        if(posi>posj)
            swap(posi,posj);
        posj--;
        int len=posj-posi+1;
        int h=1;
        int pp=0;
        while(h<=len){
            h=h<<1;
            pp++;
        }
        h=h>>1;
        pp--;
        return min(sparseTable[pp][posi],sparseTable[pp][posj-h+1]);

    }
    ~SuffixArray()
    {
        for(int i=0;i<LOG_N;i++)
        {
            if(sparseTable[i])
                delete[] sparseTable[i];
        }
    }
};
pair<int,int> longestCommonSubstring(string s,string t)
{
    int n1,n2;
    n1=s.length();
    n2=t.length();
    s+='|';
    s+=t;
    SuffixArray sf(s,true);
    vector<int> sfa=sf.getSuffixArray();
    vector<int> lcp=sf.getLcp();
    int ans=0;
    int indx=-1;
    int n=s.length();
    for(int i=1;i<n;i++)
    {
        if(sfa[i-1]<n1)
        {
            if(sfa[i]>n1)
            {
                if(lcp[i-1]>ans)
                {
                    ans=lcp[i-1];
                    indx=sfa[i-1];
                }
            }
        }
        else
        {
            if(sfa[i]<n1)
            {
                if(lcp[i-1]>ans)
                {
                    ans=lcp[i-1];
                    indx=sfa[i];
                }
            }
        }
    }
    return {indx,ans};
}
/************************************/
