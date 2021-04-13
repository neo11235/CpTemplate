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
