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
class SuffixArray{
    void sortCyclicShifts(const string& s)
    {
        memset(cnt,0,sizeof(int)*max(n,alphabet));
        for(int i=0;i<n;++i)
            ++cnt[s[i]];
        for(int i=1;i<alphabet;++i)
            cnt[i]+=cnt[i-1];
        for(int i=0;i<n;++i)
            sa[--cnt[s[i]]]=i;
        c[sa[0]]=0;
        int classes=1;
        for(int i=1;i<n;i++)
        {
            if(s[sa[i]]!=s[sa[i-1]])
                ++classes;
            c[sa[i]]=classes-1;
        }
        for(int i=n;i<2*n;++i)
        {
            c[i]=c[i-n];
        }
        for(int h=0;(1<<h)<n;++h)
        {
            for(int i=0;i<n;++i)
            {
                pn[i]=sa[i]-(1<<h);
                if(pn[i]<0)
                    pn[i]+=n;
            }
            memset(cnt,0,sizeof(int)*classes);
            for(int i=0;i<n;++i)
                ++cnt[c[pn[i]]];
            for(int i=1;i<classes;i++)
                cnt[i]+=cnt[i-1];
            for(int i=n-1;i>=0;i--)
                sa[--cnt[c[pn[i]]]]=pn[i];
            cn[sa[0]]=0;
            classes=1;
            for (int i=1;i<n;++i) {
                if (c[sa[i]]!=c[sa[i-1]]||c[sa[i]+(1<<h)]!=c[sa[i-1]+(1<<h)])
                    ++classes;
                cn[sa[i]]=classes-1;
            }
            if(classes==n)
                break;
            for(int i=n;i<2*n;++i)
            {
                cn[i]=cn[i-n];
            }
            swap(c,cn);
        }
    }
public:
    #define MAX_N 1000005
    #define LOG_N 20
    const int alphabet=128;
    int sa[MAX_N],pn[MAX_N],cnt[MAX_N],*c,*cn,data[MAX_N];
    int lcp[MAX_N];
    int pos[MAX_N];
    int sTable[MAX_N][LOG_N],LOG[MAX_N];
    int n;
    SuffixArray()
    {
        c=cn=NULL;
    }
    void buildSuffixArray(string s)
    {
        s+='$';
        n=s.length();
        for(int i=0;i<n;i++)
            data[i]=s[i];
        data[n-1]=0;
        if(c==NULL)
        {
            c=new int[MAX_N*2];
            cn=new int[MAX_N*2];
        }
        sortCyclicShifts(s);

        buildLcpArray();
        buildSparseTable();
    }
    void buildLcpArray()
    {
        for(int i=0;i<n;i++)
        {
            pos[sa[i]]=i;
        }
        int k=0;
        for(int i=0;i<n-1;i++)
        {
            int indx=pos[i];
            int i2=sa[indx-1];
            while(data[i+k]==data[i2+k])
                k++;
            lcp[indx-1]=k;
            if(k)
                k--;
        }
    }
    void buildSparseTable()
    {
    ///Remainder to implement later
    }
    int lcpQuery(int i,int j)
    {
        return 0;
    }
    ~SuffixArray()
    {
        if(c!=NULL){
            delete[] c;
            delete[] cn;
        }
    }
}SA;


/***********implementation from another source,faster than mine***************/
namespace SA{
    const int N=1e6+5;
    const int log_N=21;
    const int ALPHA= 155;
    int sa[N],ra[N],rnk[N],hg[N],n;
    int wa[N],wb[N],wws[N],wv[N];
    int lg[N], st[N][log_N];
    int cmp(int *r,int a,int b,int l){
        return (r[a]==r[b]) && (r[a+l]==r[b+l]);
    }
    void DA(int *r,int *sa,int n,int m){
        int i,j,p,*x=wa,*y=wb,*t;
        for(i=0;i<m;i++) wws[i]=0;
        for(i=0;i<n;i++) wws[x[i]=r[i]]++;
        for(i=1;i<m;i++) wws[i]+=wws[i-1];
        for(i=n-1;i>=0;i--) sa[--wws[x[i]]]=i;
        for(j=1,p=1;p<n;j*=2,m=p) {
            for(p=0,i=n-j;i<n;i++) y[p++]=i;
            for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
            for(i=0;i<n;i++) wv[i]=x[y[i]];
            for(i=0;i<m;i++) wws[i]=0;
            for(i=0;i<n;i++) wws[wv[i]]++;
            for(i=1;i<m;i++) wws[i]+=wws[i-1];
            for(i=n-1;i>=0;i--) sa[--wws[wv[i]]]=y[i];
            for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
                x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
        }
    }
    void init() {
        for(int i = 0; i <=n; i++) st[i][0] = hg[i+1];
        for(int j = 1; j < log_N; j++) {
            for(int i = 0; i <=n; i++) {
                if (i+(1<<j)-1 <= n) st[i][j] = min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
                else break;
            }
        }
        lg[0] = lg[1] = 0;
        for(int i = 2; i <= n; i++) {
            lg[i] = lg[i/2] + 1;
        }
    }
    void calheight(int *r,int *sa,int n){
        int i,j,k=0;
        for(i=1;i<=n;i++) rnk[sa[i]]=i;
        for(i=0;i<n;hg[rnk[i++]]=k)
            for(k?k--:0,j=sa[rnk[i]-1];r[i+k]==r[j+k];k++);
    }
    void create_sa(string  &s) {
        n = s.size();
        for(int i=0;i<max(n+1,ALPHA);i++) sa[i]=ra[i]=rnk[i]=hg[i]=wa[i]=wb[i]=wws[i]=wv[i]=0;
        for (int i = 0; i < n; i++) ra[i] = s[i];
        DA(ra,sa,n+1,ALPHA);
        calheight(ra,sa,n);
        init();
    }
    //0 indexed
    int query(int l, int r) {
        int pl=rnk[l];
        int pr=rnk[r];
        if(pl>pr)
            swap(pl,pr);
        pr--;
        int x=lg[pr-pl+1];
        return min(st[pl][x],st[pr-(1<<x)+1][x]);
    }
}
/*********************************************************************/
