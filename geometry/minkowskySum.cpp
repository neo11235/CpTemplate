struct pt{
    ll x,y;
    pt operator+(const pt& p)const
    {
        return pt{x+p.x,y+p.y};
    }
    pt operator-(const pt& p)const
    {
        return pt{x-p.x,y-p.y};
    }
    ll cross(const pt& p)const
    {
        return x*p.y-y*p.x;
    }
};
void reorderPolygon(vector<pt>& P)//p must be ordered counterclockwise
{
    int pos=0;
    for(int i=1;i<(int)P.size();i++)
    {
        if(P[i].y<P[pos].y||(P[i].y==P[pos].y&&P[i].x<P[pos].x))
        {
            pos=i;
        }
    }
    rotate(P.begin(),P.begin()+pos,P.end());
}
vector<pt> minkowski(vector<pt> P,vector<pt> Q)//p and q is assumed to be sorted
{
    reorderPolygon(P);
    reorderPolygon(Q);
    P.push_back(P[0]);
    P.push_back(P[1]);
    Q.push_back(Q[0]);
    Q.push_back(Q[1]);
    vector<pt> res;
    int i=0,j=0;
    while(i<P.size()-2||j<Q.size()-2)
    {
        res.push_back(P[i]+Q[j]);
        auto cross=(P[i+1]-P[i]).cross(Q[j+1]-Q[j]);
        if(cross>=0)
            ++i;
        if(cross<=0)
            ++j;
    }
    return res;
}
//some useful function
bool cw(pt& a,pt&b,pt&c){
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y)<=0;
}
bool ccw(pt& a,pt&b,pt&c){
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y)>=0;
}
double minDis0(pt a,pt b)
{
    double ans=min(sqrt((double)a.x*a.x+a.y*a.y),
                   sqrt((double)b.x*b.x+b.y*b.y));
    if((a.x-b.x)*a.x+(a.y-b.y)*a.y>=0)
    {
        ans=min(ans,((double)(a.x*b.y-b.x*a.y))/sqrt(sqr(a.x-b.x)+sqr(a.y-b.y)));
    }
    return ans;
}
