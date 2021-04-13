template<class T>//signed area
T area(vector<vector2d<T> >& polygon)
{
    int n=polygon.size();
    if(n<3)
        return (T)0;
    T ans=0;
    for(int i=0;i<n-1;i++)
    {
        ans+=polygon[i].x*polygon[i+1].y;
        ans-=polygon[i].y*polygon[i+1].x;
    }
    ans+=polygon[n-1].x*polygon[0].y;
    ans-=polygon[n-1].y*polygon[0].x;
    return ans/2;
}
