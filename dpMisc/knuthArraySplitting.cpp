/**********************************************/
//knuth optimization
/**********************************************/
ll dp[1002][1002];
int indx[1002][1002];
int d[1002];
int cd[1002];
//assumes d and cd (cumulative sum) are calculated and 1 indexed
void knuthArraySplitting(int n)
{
    for(int i=1;i<=n;++i)
    {
        dp[i][i]=0;
        indx[i][i]=i;
    }
    for(int l=2;l<=n;++l)
    {
        int i=1,j=l;
        while(j<=n)
        {
            dp[i][j]=LLONG_MAX;
            for(int k=indx[i][j-1];k<=indx[i+1][j];++k)
            {
                if(dp[i][k]+dp[k+1][j]+cd[j]-cd[i-1]<dp[i][j])
                {
                    dp[i][j]=dp[i][k]+dp[k+1][j]+cd[j]-cd[i-1];
                    indx[i][j]=k;
                }
            }
            ++i;
            ++j;
        }
    }
}
