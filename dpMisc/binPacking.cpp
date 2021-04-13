int lst[1<<20],dp[1<<20];
int main()
{
    int n,x,i,j,data[20];
    sci(n,x);
    for(i=0;i<n;i++)
    {
        sci(data[i]);
    }
    dp[0]=1;
    for(i=1;i<(1<<n);i++)
    {
        pii bst={n+1,0};
        for(j=0;j<n;j++)
        {
            if(i&(1<<j))
            {
                int l=i^(1<<j);
                pii op;
                if(lst[l]+data[j]<=x)
                {
                    op={dp[l],lst[l]+data[j]};
                }
                else
                {
                    op={dp[l]+1,data[j]};
                }
                bst=min(bst,op);
            }
        }
        dp[i]=bst.first;
        lst[i]=bst.second;
    }
    cout<<dp[(1<<n)-1]<<endl;
}
