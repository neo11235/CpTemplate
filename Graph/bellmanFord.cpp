WGraph G;
vi vis;
ll dp1[2500];
ll dp2[2500];
void belmanFord(int n)
{
    int i,j;

    for(i=0;i<n;i++)
    {
        dp1[i]=dp2[i]=infl;
    }
    dp1[0]=dp2[0]=0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(dp1[j]!=infl){
            for(auto e:G[j])
            {

                dp2[e.first]=min(dp2[e.first],dp1[j]+e.second);
            }
            }
        }
        if(i!=n-1){
            for(j=0;j<n;j++)
            {
                if(dp2[j]!=dp1[j])
                {
                    dp1[j]=dp2[j];
                }
            }
        }
    }

}


/******/
WGraph G;
vi vis;
vi parent;
vi negCycle;
ll dp[2500];
bool detectNegCycle(int n)
{
    memset(dp,0,sizeof(dp));
    int i,j;
    int c;
    for(i=0;i<n;i++)
    {
        c=-1;
        for(j=0;j<n;j++)
        {
         for(auto e:G[j])
            {
                if(dp[j]+e.second<dp[e.first])
                {
                    dp[e.first]=dp[j]+e.second;
                    parent[e.first]=j;
                    c=e.first;
                }
            }
        }
    }
    if(c==-1)
        return false;
    for(i=0;i<n;i++)
        c=parent[c];
    int x=c;
    negCycle.push_back(c);
    c=parent[c];
    while(c!=x)
    {
        negCycle.push_back(c);
        c=parent[c];
    }
    negCycle.push_back(c);
    reverse(negCycle.begin(),negCycle.end());
    return true;

}

