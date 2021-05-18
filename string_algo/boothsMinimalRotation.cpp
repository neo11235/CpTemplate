///tested on cses
int minimalRotation(string s)
{
    s+=s;
    int n=s.length();
    vector<int> f(n,-1);
    int k=0;
    int i;
    for(int j=1;j<n;j++)
    {
        char sj=s[j];
        i=f[j-k-1];
        while(i!=-1&&sj!=s[k+i+1])
        {
            if(sj<s[k+i+1])
                k=j-i-1;
            i=f[i];
        }
        if(sj!=s[k+i+1])
        {
            if(sj<s[k])
            {
                k=j;
            }
            f[j-k]=-1;
        }
        else
        {
            f[j-k]=i+1;
        }
    }
    return k;
}
