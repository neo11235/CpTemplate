ll g[500][500];
void floyedWarshal(int n)
{
    //g[i][i] should be zero
    for(int k=0;k<n;k++)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(g[i][k]<LLONG_MAX&&g[k][j]<LLONG_MAX)
                    g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
            }
        }
    }
}
