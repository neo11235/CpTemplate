int length_union(const vector<pair<int,int> >&a)
{
    int n=a.size();
    vector<pair<int,bool> > x(2*n);
    for(int i=0;i<n;i++)
    {
        x[2*i]={a[i].first,false};
        x[2*i+1]={a[i].second,true};
    }
    sort(x.begin(),x.end());
    int result=0;
    int c=0;
    for(int i=0;i<(2*n);i++)
    {
        if(i>0&&x[i].first>x[i-1].first&&c>0)
            result+=x[i].first-x[i-1].first;
        if(x[i].second)
            c--;
        else
            c++;
    }
    return result;
}
