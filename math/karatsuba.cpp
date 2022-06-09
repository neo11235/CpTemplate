//runtime O(n^1.5)
vector<int> mult(vector<int>& a,vector<int>& b)
{
    int n=a.size();
    if(n==1)
        return {a[0]*b[0]};
    int n2=n/2;
    vi a0(n2),a1(n2),b0(n2),b1(n2),z1,z2,z0;
    copy(a.begin(),a.begin()+n2,a0.begin());
    copy(a.begin()+n2,a.end(),a1.begin());
    copy(b.begin(),b.begin()+n2,b0.begin());
    copy(b.begin()+n2,b.end(),b1.begin());
    z0=mult(a0,b0);
    z2=mult(a1,b1);
    for(int i=0;i<n2;++i)
    {
        a0[i]+=a1[i];
        b0[i]+=b1[i];
    }
    z1=mult(a0,b0);
    for(int i=0;i<n-1;++i)
        z1[i]-=(z0[i]+z2[i]);
    vi res(n*2-1,0);
    for(int i=0;i<n-1;++i){
        res[i]+=z0[i];
        res[i+n2]+=z1[i];
        res[i+n]+=z2[i];
    }
    return res;
}
int* mult(int* a,int* b,int n)
{
    if(n==1){
        int* res=(int*)malloc(sizeof(int));
        res[0]=a[0]*b[0];
        return res;
    }
    int n2=n/2;
    int a0[n2],a1[n2],b0[n2],b1[n2],*z1,*z2,*z0;
    copy(a,a+n2,a0);
    copy(a+n2,a+n,a1);
    copy(b,b+n2,b0);
    copy(b+n2,b+n,b1);
    z0=mult(a0,b0,n2);
    z2=mult(a1,b1,n2);
    for(int i=0;i<n2;++i)
    {
        a0[i]+=a1[i];
        b0[i]+=b1[i];
    }
    z1=mult(a0,b0,n2);
    for(int i=0;i<n-1;++i)
        z1[i]-=(z0[i]+z2[i]);
    int* res=(int*)malloc(sizeof(int)*(2*n-1));
    memset(res,0,sizeof(int)*(2*n-1));
    for(int i=0;i<n-1;++i){
        res[i]+=z0[i];
        res[i+n2]+=z1[i];
        res[i+n]+=z2[i];
    }
    free(z1);
    free(z2);
    free(z0);
    return res;
}
