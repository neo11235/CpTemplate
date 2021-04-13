

template<class T>
int bSearch(vector<T>& sortedArray,T el)
{
    int l=0,r=(int)sortedArray.size()-1;
    while(l<r){
        int mid=(l+r)/2;
        if(sortedArray[mid]<=el)
        {
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    if(sortedArray[l]<=el)
        return l+1;
    return l;
}

template<class T>
int bSearch(vector<pair<T,T> >& sortedArray,T el)
{
    int l=0,r=(int)sortedArray.size()-1;
    while(l<r)
    {
        int mid=(l+r)/2;
        if(sortedArray[mid].first<=el)
            l=mid+1;
        else
            r=mid-1;
    }
    if(sortedArray[l].first<=el)
        return l+1;
    return l;
}


//bisection
double pres=1e-9;
bool can(double val)
{
}
double binarySearch(double l,double r,double e)
{
    double mid;
    while((r-l)>e)
    {
        mid=(l+r)/2;
        if(can(mid))
            r=mid;
        else
            l=mid;

    }
    return (l+r)/2;
}
