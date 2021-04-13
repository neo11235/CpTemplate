int LIS(vector<int> & a)
{
    int n=a.size();
    int inf=1e9+1;
    vector<int> dp(n+1,inf);
    dp[0]=-inf;
    int i;
    for(i=0;i<n;i++)
    {
        int j=upper_bound(dp.begin(),dp.end(),a[i])-dp.begin();
        if(dp[j-1]<a[i]&&a[i]<dp[j])
        {
            dp[j]=a[i];
        }
    }
    int ans=0;
    for(i=0;i<=n;i++)
    {
        if(dp[i]<inf)
            ans=i;
    }
    return ans;
}
