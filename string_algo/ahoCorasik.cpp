#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define vi vector<int>
#define triple pair<pair<int,int>,int>
#define vpii vector<pii >
#define Graph vector<vector<int> >
#define WGraph vector<vector<pii>>
#define pli pair<ll,int>
#define pll pair<ll,ll>

#define sci1(a) scanf("%d",&a)
#define sci2(a,b) scanf("%d %d",&a,&b)
#define sci3(a,b,c) scanf("%d %d %d",&a,&b,&c)
#define scs(s) scanf("%s",s)
#ifndef GET_MACRO

#define GET_MACRO(__1,__2,__3,NAME,...) NAME

#endif // GET_MACRO

#define sci(...) GET_MACRO(__VA_ARGS__,sci3,sci2,sci1)(__VA_ARGS__)

#define read freopen("input.txt","r",stdin)
#define write freopen("output.txt","w",stdout)
#define infl 0xfffffffffffffffll
#define infi  0x1fffffff
#define LSB(i) ((i)&(-(i)))
#define mp(a,b) make_pair(a,b)

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);

#define bound(i,j,n,m) ((i)<n&&(j)<m&&(i)>=0&&(j)>=0)

#define bucket 500

const int AS=26;
struct vertex{
    int next[AS];
    bool leaf=false;
    int p=-1;
    int length=0;
    char pch;
    int link=-1;
    int go[AS];
    vertex(int p=-1,char ch='$'):p(p),pch(ch)
    {
        fill(begin(next),end(next),-1);
        fill(begin(go),end(go),-1);
    }
};
#define MX_SIZE 1000000
vector<vertex> trie(MX_SIZE);
int cur_size=1;
void addString(string const& s)
{
    int v=0;
    for(char ch:s)
    {
        int c=ch-'a';
        if(trie[v].next[c]==-1)
        {
            trie[v].next[c]=cur_size;
            trie[cur_size].p=v;
            trie[cur_size].pch=ch;
            cur_size++;
        }
        v=trie[v].next[c];
    }
    trie[v].length=s.length();
    trie[v].leaf=true;
}
int go(int v,char ch);
int get_link(int v)
{
    if(trie[v].link==-1)
    {
        if(v==0||trie[v].p==0)
            trie[v].link=0;
        else
            trie[v].link=go(get_link(trie[v].p),trie[v].pch);
    }
    return trie[v].link;
}
int go(int v,char ch)
{
    int c=ch-'a';
    if(trie[v].go[c]==-1)
    {
        if(trie[v].next[c]!=-1)
            trie[v].go[c]=trie[v].next[c];
        else
            trie[v].go[c]=v==0?0:go(get_link(v),ch);
    }
    return trie[v].go[c];
}
ll dp[5001];
int main()
{
    //read;
    fastio;
    string str;
    string tmp;
    cin>>str;
    int i,j,k;
    cin>>k;
    for(i=0;i<k;i++)
    {
        cin>>tmp;
        addString(tmp);
    }
    dp[0]=1;
    int l=str.length();
    int curV=0;
    int tV;
    for(i=1;i<=l;i++)
    {
        curV=go(curV,str[i-1]);
        tV=curV;
        while(tV!=0)
        {
            if(trie[tV].leaf){
                dp[i]+=dp[i-trie[tV].length];
                dp[i]%=1000000007ll;
            }
            tV=get_link(tV);
        }
    }
    cout<<dp[l]<<endl;

}


const int AS=26;
struct vertex{
    int next[AS];
    bool leaf=false;
    multiset<int> st=NULL;
    int mx=0;
    int p=-1;
    int length=0;
    char pch;
    int link=-1;
    int elink=-1;
    int go[AS];
    vertex(int p=-1,char ch='$'):p(p),pch(ch)
    {
        fill(begin(next),end(next),-1);
        fill(begin(go),end(go),-1);
    }
};
#define MX_SIZE 1000000
vector<vertex> trie(MX_SIZE);
int cur_size=1;
int addString(string const& s)
{
    int v=0;
    for(char ch:s)
    {
        int c=ch-'a';
        if(trie[v].next[c]==-1)
        {
            trie[v].next[c]=cur_size;
            trie[cur_size].p=v;
            trie[cur_size].pch=ch;
            cur_size++;
        }
        v=trie[v].next[c];
    }
    trie[v].length=s.length();
    trie[v].st.insert(0);
    trie[v].leaf=true;
    return v;
}
int go(int v,char ch);
int get_link(int v)
{
    if(trie[v].link==-1)
    {
        if(v==0||trie[v].p==0)
            trie[v].link=0;
        else
            trie[v].link=go(get_link(trie[v].p),trie[v].pch);
    }
    return trie[v].link;
}
int go(int v,char ch)
{
    int c=ch-'a';
    if(trie[v].go[c]==-1)
    {
        if(trie[v].next[c]!=-1)
            trie[v].go[c]=trie[v].next[c];
        else
            trie[v].go[c]=v==0?0:go(get_link(v),ch);
    }
    return trie[v].go[c];
}
int tmp_ar[1000000];
void aho_dfs(){//construct all elink
    stack<int> stck;
    stck.push(0);
    while(!stck.empty()){
        int node=stck.top();
        int v=node;
        stck.pop();
        int i,j;
        while(1){
            if(trie[v].elink==-1){
                i=1;
                tmp_ar[0]=v;
                while(v=get_link(v)){
                    if(trie[v].leaf)break;
                    if(trie[v].elink!=-1)
                    {
                        v=trie[v].elink;
                        break;
                    }
                    tmp_ar[i]=v;
                    i++;
                }
                for(j=0;j<i;j++)trie[tmp_ar[j]].elink=v;
            }
            else{
                v=trie[v].elink;
            }
            if(v==0)break;
        }
        for(i=0;i<AS;i++){
            if(trie[node].next[i]!=-1){
                stck.push(trie[node].next[i]);
            }
        }
    }
    return;
}

///aho corasick///
namespace AC{
    const int AlphabetSize=26;
    struct Vertex{
        int next[AlphabetSize];
        int go[AlphabetSize];
        int leaf=-1;
        int p=-1;
        char pch;
        int elink=-1;//link to the maximum proper suffix of current string
        int vlink=-1;//link to the maximum proper suffix of current string which is also a string in the given set
        Vertex(int  p=-1,char pch='$'):p(p),pch(pch)
        {
            memset(next,-1,sizeof(next));
            memset(go,-1,sizeof(go));
        }
        void reset()
        {
            memset(next,-1,sizeof(next));
            memset(go,-1,sizeof(go));
            leaf=p=elink=vlink=-1;
        }
    };
    const int MaxLength=1e6;
    Vertex trie[MaxLength];
    int curSize=1;

    //returns identifier of the string currently at the end vertex of s
    int addString(const string& s,int id)//id should be unique identifier of the string
    {
        int v=0;
        for(char ch:s)
        {
            int c=ch-'a';
            if(trie[v].next[c]==-1)
            {
                trie[curSize].p=v;
                trie[curSize].pch=ch;
                trie[v].next[c]=curSize++;
            }
            v=trie[v].next[c];
        }
        if(trie[v].leaf==-1)
            trie[v].leaf=id;
        return trie[v].leaf;
    }
    int addString(char* s,int id)
    {
        int v=0;
        while(*s!='\0')
        {
            int c=*s-'a';
            if(trie[v].next[c]==-1)
            {
                trie[curSize].p=v;
                trie[curSize].pch=*s;
                trie[v].next[c]=curSize++;
            }
            v=trie[v].next[c];
            ++s;
        }
        if(trie[v].leaf==-1)
            trie[v].leaf=id;
        return trie[v].leaf;
    }

    //should be called after adding all string to the trie
    void constructAutomation(void)
    {
        trie[0].elink=0;
        trie[0].vlink=0;//assume that empty string always exist in the set
        queue<int> Q;
        for(int i=0;i<AlphabetSize;++i)
        {
            trie[0].go[i]=(trie[0].next[i]==-1?0:trie[0].next[i]);
            if(trie[0].next[i]==-1)
            {
                trie[0].go[i]=0;
            }
            else
            {
                trie[0].go[i]=trie[0].next[i];
                Q.push(trie[0].next[i]);
            }
        }
        while(!Q.empty())
        {
            int v=Q.front();
            Q.pop();
            int p=trie[v].p;
            char pch=trie[v].pch;
            trie[v].elink=trie[trie[p].elink].go[pch-'a'];
            if(trie[v].elink==v)
                trie[v].elink=0;
            if(trie[trie[v].elink].leaf!=-1)
                trie[v].vlink=trie[v].elink;
            else
                trie[v].vlink=trie[trie[v].elink].vlink;
            for(int i=0;i<AlphabetSize;++i)
            {
                if(trie[v].next[i]==-1)
                {
                    trie[v].go[i]=trie[trie[v].elink].go[i];
                }
                else
                {
                    trie[v].go[i]=trie[v].next[i];
                    Q.push(trie[v].next[i]);
                }
            }
        }
    }
    void printAutomation()//for debugging
    {
        cout<<"Next\n";
        for(int i=0;i<curSize;++i)
        {
            for(int j=0;j<AlphabetSize;++j)
                cout<<trie[i].next[j]<<' ';
            cout<<'\n';
        }
        cout<<"End of Next\n\n";

        cout<<"Automation\n";
        for(int i=0;i<curSize;++i)
        {
            cout<<i<<':';
            for(int j=0;j<AlphabetSize;++j)
                cout<<trie[i].go[j]<<' ';
            cout<<'\n';
        }
        cout<<"End Automation\n\n";

        cout<<"Elinks\n";
        for(int i=0;i<curSize;++i)
        {
            cout<<i<<' '<<trie[i].elink<<'\n';
        }
        cout<<"End of Elinks\n\n";
    }
    int go(int v,char ch)//implementation of function that older code used
    {
        return trie[v].go[ch-'a'];
    }
    int getLink(int v)//implementation of function that older code used
    {
        return trie[v].elink;
    }

    int nMatch[MaxLength];
    const int MaxNumberOfString=1e6;
    int ans[MaxNumberOfString];

    //O(n+m^2) where m is the number of distinct length of string in the set added to the structure
    void dfs(int v)
    {
        if(trie[v].leaf!=-1)
        {
            int vv=v;
            while(vv>0)
            {
                ans[trie[vv].leaf]+=nMatch[v];
                vv=trie[vv].vlink;
            }
        }
        for(int i=0;i<AlphabetSize;++i)
        {
            if(trie[v].next[i]==-1)
                continue;
            dfs(trie[v].next[i]);
        }
    }
    //O(n)
    void reverseBFS(int v)//should be faster than dfs,but in loj its runtime was slowar than about 100 ms than dfs,but was faster in cses
    {
        stack<int> st;
        queue<int> q;
        q.push(v);
        while(!q.empty())
        {
            v=q.front();
            q.pop();
            st.push(v);
            for(int i=0;i<AlphabetSize;++i)
            {
                if(trie[v].next[i]!=-1)
                {
                    q.push(trie[v].next[i]);
                }
            }
        }
        while(!st.empty())
        {
            v=st.top();
            st.pop();
            if(trie[v].leaf==-1)
                continue;
            ans[trie[v].leaf]+=nMatch[v];
            nMatch[trie[v].vlink]+=nMatch[v];
        }
    }
    void computeAllMatch(const string& s)
    {
        int v=0;
        for(char ch:s)
        {

            v=trie[v].go[ch-'a'];
            if(trie[v].leaf!=-1)
            {
                ++nMatch[v];
            }
            else
                ++nMatch[trie[v].vlink];
        }
        //dfs(0);
        reverseBFS(0);
    }
    void reset(){
        for(int i=0;i<curSize;++i)
        {
            trie[i].reset();
            nMatch[i]=ans[i]=0;
        }
        curSize=1;
    }
}
