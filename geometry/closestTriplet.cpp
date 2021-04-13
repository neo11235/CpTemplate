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
//pii curMin;
double dmin=inf;
void updateMin(Point a,Point b,Point c)
{
    dmin=min(dmin,dist(a,b)+dist(b,c)+dist(a,c));
    ///if sollution requires id's of the point save the ids here
}
void closestTriplet(int l,int r)
{
    if(r-l+1==3)
    {
        updateMin(ysorted[l],ysorted[l+1],ysorted[l+2]);
        sort(ysorted.begin()+l,ysorted.begin()+r+1,cmp_y());
        return;
    }
    if(r-l+1<3){
        sort(ysorted.begin()+l,ysorted.begin()+r+1,cmp_y());
        return;
    }
    int mid=(l+r)/2;
    int midx=ysorted[mid].x;
    closestTriplet(l,mid);
    closestTriplet(mid+1,r);
    merge(ysorted.begin()+l,ysorted.begin()+mid+1,ysorted.begin()+mid+1,\
          ysorted.begin()+r+1,temp.begin(),cmp_y());
    copy(temp.begin(),temp.begin()+r-l+1,ysorted.begin()+l);
    int k=0;

    for(int i=l;i<=r;i++)
    {
        if(abs(ysorted[i].x-midx)<dmin/2)
        {
            for(int j=k-1;j>0&&ysorted[i].y-temp[j].y<dmin/2;j--)
            {
                for(int m=j-1;m>=0&&ysorted[i].y-temp[m].y<dmin/2;m--)
                {
                    updateMin(ysorted[i],temp[j],temp[m]);
                }
            }
            temp[k++]=ysorted[i];
        }
    }
}


void solvecases(int n)
{
    odata.resize(n);
    ysorted.resize(n);
    temp.resize(n);
    for(int i=0;i<n;i++)
    {
        cin>>odata[i].x>>odata[i].y;
        odata[i].id=i;
        ysorted[i].x=odata[i].x;
        ysorted[i].y=odata[i].y;
        ysorted[i].id=odata[i].id;
    }
    sort(ysorted.begin(),ysorted.end(),cmp_x());
    closestTriplet(0,n-1);
    cout<<dmin<<'\n';

}
