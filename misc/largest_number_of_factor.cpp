#include <bits/stdc++.h>
using namespace std;
#define fastio   ios_base::sync_with_stdio(false);cin.tie(NULL)
#define vi vector<int>
#define Graph vector<vector<int> >
#define mp(i,j) make_pair(i,j)
#define ll unsigned long long
#define pii pair<int,int>
#define vll vector<ll>
#define pll pair<ll,ll>
int prime[25];
int lim[25];
bool is_prime(int n){
    if(n<2)return 0;
    double sq=sqrt((double)n);
    int l=(int)sq;
    int i;
    for(i=2;i<=l;i++){
        if((n%i)==0)return false;
    }
    return true;
}
void build()
{
    int j=0;
    for(int i=2;j<25;++i)
    {
        if(is_prime(i))
        {
            prime[j]=i;
            ++j;
        }
    }
    ll debug=1;

    for(int i=0;i<25;++i)
        lim[i]=1;
    for(int i=0;i<6;++i)
        lim[i]=2;
    lim[0]=10;
    lim[1]=8;
    lim[2]=4;
    lim[3]=3;
}
vector<pll> ans;
void dfs(ll num,ll f,int j,ll n)
{
    if(num>n)
        return;
    ans.push_back(mp(f,num));
    for(int i=0;i<lim[j];++i)
    {
        double l=log10(num)+log10(prime[j]);
        if(l>18+1e-5)
            break;
        num*=prime[j];
        dfs(num,f*(i+2),j+1,n);
    }
}
int main()
{
    fastio;
    build();
    int q;
    cin>>q;
    for(int i=0;i<q;++i)
    {
        ll n;
        cin>>n;
        dfs(1ll,1ll,0,n);
        pll r=ans[0];
        for(auto e:ans)
        {
            if(e.first>r.first)
            {
                r=e;
            }
            else if(e.first==r.first&&e.second<r.second)
            {
                r=e;
            }
        }
        cout<<r.second<<' '<<r.first<<'\n';
        ans.clear();
    }

}
/*
1
1000000000000000000
*/
