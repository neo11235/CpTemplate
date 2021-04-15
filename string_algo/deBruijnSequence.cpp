class BrSe{
    int power(int a,int b)
    {
        int ans=1;
        while(b--)
        {
            ans*=a;
        }
        return ans;
    }
    int add1(int* n,int base,int len)
    {
        for(int i=len-1;i>=0;i--)
        {
            ++n[i];
            if(n[i]==base)
            {
                n[i]=0;
            }
            else
            {
                return 0;
            }
        }
        return 1;
    }
public:
    vector<set<int> >  G;
    vi sol;
    vi indeg;
    BrSe(){}
    void etour(int node)
    {
        stack<int> dStack;
        dStack.push(node);
        while(!dStack.empty())
        {
            int tnode=dStack.top();
            if(G[tnode].empty())
            {
                sol.push_back(tnode);
                dStack.pop();
            }
            else{
                int v=*G[tnode].begin();
                dStack.push(v);
                G[tnode].erase(G[tnode].begin());
                //G[v].erase(G[v].find(tnode));
            }
        }
        reverse(sol.begin(),sol.end());
    }
    /// de bruijn sequence of k alphabet of length length
    vector<int> B(int k,int n)//k^n<1e7
    {
        int len=power(k,n-1);
        G.assign(len,set<int>());
        sol.clear();
        indeg.assign(len,0);
        int cnt[n-1];
        memset(cnt,0,sizeof(int)*(n-1));
        int cur,nxt;
        do
        {
            cur=0;
            int i=0;
            for(;i<n-1;i++)
            {
                if(cnt[i])
                    break;
            }
            nxt=0;
            for(int j=i+1;j<n-1;j++)
            {
                nxt*=k;
                nxt+=cnt[j];
            }
            nxt*=k;
            for(;i<n-1;i++)
            {
                cur*=k;
                cur+=cnt[i];
            }
            for(i=0;i<k;i++)
            {
                G[cur].insert(nxt+i);
            }

        }while(!add1(cnt,k,n-1));
        etour(0);
        vector<int> sol2(sol.begin(),sol.end());
        for(auto& e:sol2)
        {
            e%=k;
        }
        return sol2;
    }
};
