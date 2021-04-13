struct Point{
    int x,y;
    int id;
    Point(){}
    Point(int x,int y,int id):x(x),y(y),id(id){}
};
struct cmp_x
{
    bool operator()(const Point& a,const Point& b) const
    {
        return a.x<b.x||(a.x==b.x&&a.y<b.y);
    }
};
struct cmp_y
{
    bool operator()(const Point& a,const Point& b)const
    {
        return a.y<b.y||(a.y==b.y&&a.x<b.x);
    }
};
double dist(Point& a,Point& b)
{
    return sqrt((double)(a.x-b.x)*(a.x-b.x)+(double)(a.y-b.y)*(a.y-b.y));
}
///double or long double
const double inf=1e9;
vector<Point> odata;//original data in order of input
vector<Point> xsorted;//odata sorted in increasing order of x
vector<Point> ysorted;//will be sorted by the algorithm just copy xsorted initially
vector<Point> temp;///resize it to same size as odata
pii curMin;
double dmin=inf;
void closestPair(int l,int r)
{
    if(l==r)
        return;
    int mid=(l+r)/2;
    int midx=ysorted[mid].x;
    closestPair(l,mid);
    closestPair(mid+1,r);
    merge(ysorted.begin()+l,ysorted.begin()+mid+1,ysorted.begin()+mid+1,\
          ysorted.begin()+r+1,temp.begin(),cmp_y());
    copy(temp.begin(),temp.begin()+r-l+1,ysorted.begin()+l);
    int k=0;
    for(int i=l;i<=r;i++)
    {
        if(abs(ysorted[i].x-midx)<dmin)
        {
            for(int j=k-1;j>=0&&ysorted[i].y-temp[j].y<dmin;j--)
            {
                double tdist=dist(ysorted[i],temp[j]);
                if(tdist<dmin)
                {
                    dmin=tdist;
                    curMin={ysorted[i].id,temp[j].id};
                }
            }
            temp[k++]=ysorted[i];
        }
    }
}
void solvecases(int cse)
{
    int n;
    cin>>n;
    odata.resize(n);
    xsorted.resize(n);
    ysorted.resize(n);
    temp.resize(n);
    for(int i=0;i<n;i++)
    {
        cin>>odata[i].x>>odata[i].y;
        odata[i].id=i;
    }
    copy(odata.begin(),odata.end(),xsorted.begin());
    sort(xsorted.begin(),xsorted.end(),cmp_x());
    copy(xsorted.begin(),xsorted.end(),ysorted.begin());
    closestPair(0,n-1);
    if(curMin.first>curMin.second)
        swap(curMin.first,curMin.second);
    cout<<curMin.first<<' '<<curMin.second<<' '<<dmin<<'\n';
}
