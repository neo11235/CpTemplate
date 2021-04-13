
///O(n^3) v bad brute force implementation,implement better algorithm later
template<class T>
int area(pair<T,T>& p1,pair<T,T>& p2,pair<T,T>& p3){
    return (p1.first*p2.second+p2.first*p3.second+p3.first*p1.second
            -p1.second*p2.first-p2.second*p3.first-p3.second*p1.first);
}
template<class T>
bool inside(pair<T,T>& a,pair<T,T>& b,pair<T,T>& c,pair<T,T>& p)
{
    int ar=abs(area(a,b,c));
    int t=abs(area(a,b,p))+abs(area(b,c,p))+abs(area(c,a,p));
    return ar==t;
}
template<class T>
void triangulate(vector<pair<T,T> > p,vector<pair<T,T> >&out)
{
    int pindx=0;
    if((int)p.size()<=3)
    {
        out.resize(p.size());
        copy(p.begin(),p.end(),out.begin());
        return;
    }
    while(p.size()>3)
    {
        int n=(int)p.size();
        int i,j,k;
        for(i=0;i<n;i++)
        {
            j=i+1;
            k=i+2;
            j=j>=n?j-n:j;
            k=k>=n?k-n:k;
            if(area(p[i],p[j],p[k])<0)
            {
                continue;
            }
            bool chk=true;
            for(int l=0;l<n;l++)
            {
                if(l==i||l==j||l==k)
                    continue;
                if(inside(p[i],p[j],p[k],p[l]))
                {
                    chk=false;
                    break;
                }
            }
            if(chk)
                break;
        }
        out[pindx++]=p[i];
        out[pindx++]=p[j];
        out[pindx++]=p[k];
        p.erase(p.begin()+j);
    }
    for(auto e:p)
        out[pindx++]=e;
}
