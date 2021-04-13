
template<class T>
ll maxSubarray(vector<T> Array){
    ll sol=0;
    ll tmp=0;
    int i,n=(int)Array.size();
    for(i=0;i<n;i++)
    {
        tmp+=(ll)Array[i];
        if(tmp<0)
            tmp=0;
        sol=max(sol,tmp);
    }
    return sol;
}
