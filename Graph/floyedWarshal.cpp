ll G[500][500];
void floyedWarshal(int n)
{
    //G[i][i] should be zero
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(G[i][k]<infl&&G[k][j]<infl)
                    G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
            }
        }
    }
}
