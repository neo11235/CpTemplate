int numberOfDistinctLine(vector<pii>&d)
{
    int n=(int)d.size();
    map<pair<pii,int>,int> line;
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            int a,b,c;
            a=d[j].second-d[i].second;
            b=-d[j].first+d[i].first;
            c=d[i].second*(d[j].first-d[i].first)-d[i].first*(d[j].second-d[i].second);
            if(a<0)
            {
                a=-a;
                b=-b;
                c=-c;
            }
            if(a==0)
            {
                if(b<0)
                {
                    b=-b;
                    c=-c;
                }
                c/=b;
                b=1;
            }
            else if(b==0)
            {
                if(a<0)
                {
                    a=-a;
                    c=-c;
                }
                c/=a;
                a=1;
            }
            else
            {
                int g=__gcd(abs(a),abs(b));
            g=__gcd(g,abs(c));
            a/=g;
            b/=g;
            c/=g;
            }
            line[mp(mp(a,b),c)]++;
        }
    }
    return line.size();
}
