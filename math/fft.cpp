//first implementation,slower,recursive
vector<complex<double> > W(1000000);
const double pi=3.1415926535897932384;
vector<complex<double> > fTransform(vector<complex<double> >& a,int add)
{
    int n=(int)a.size();
    assert((n&(n-1))==0);
    if(n==1)
    {
        return {complex<double>(a[0])};
    }
    int n2=n/2;
    vector<complex<double> > a1(n2),a2(n2);
    for(int i=0;i<n;i+=2)
    {
        a1[i>>1]=a[i];
    }
    for(int i=1;i<n;i+=2)
    {
        a2[i>>1]=a[i];
    }
    vector<complex<double> > r1=fTransform(a1,add<<1);
    vector<complex<double> > r2=fTransform(a2,add<<1);
    vector<complex<double> > res(n);
    for(int i=0;i<n2;++i)
    {
        res[i]=r1[i]+W[i*add]*r2[i];
    }
    for(int i=n2;i<n;++i)
    {
        res[i]=r1[i-n2]+W[i*add]*r2[i-n2];
    }
    return res;
}
vector<ll> mult(vector<int>& a,vector<int>& b)
{
    int n=a.size();
    for(int i=0;i<n;++i)
    {
        W[i]=complex<double>(cos(2*pi*i/n),sin(2*pi*i/n));
    }
    vector<complex<double> > tmp(n);
    for(int i=0;i<n;++i)
        tmp[i]=complex<double>(a[i],0);
    vector<complex<double> > t1=fTransform(tmp,1);
    for(int i=0;i<n;++i)
        tmp[i]=complex<double>(b[i],0);
    vector<complex<double> > t2=fTransform(tmp,1);
    for(int i=0;i<n;++i)
    {
        t1[i]*=t2[i];
    }
    for(int i=0;i<n;++i)
    {
        W[i]=complex<double>(cos(2*pi*i/n),-sin(2*pi*i/n));
    }
    t2=fTransform(t1,1);
    vector<ll> res(n);
    for(int i=0;i<n;++i)
    {
        res[i]=(ll)round(t2[i].real()/n);
    }
    return res;
}

///*********************************************///
///********iterative version,faster*****************///
namespace fft{
    //typedef complex<double> CD;
    struct CD {
        double x, y;
        CD(double x=0, double y=0) :x(x), y(y) {}
        CD operator+(const CD& o) { return {x+o.x, y+o.y};}
        CD operator-(const CD& o) { return {x-o.x, y-o.y};}
        CD operator*(const CD& o) { return {x*o.x-y*o.y, x*o.y+o.x*y};}
        void operator /= (double d) { x/=d; y/=d;}
        double real() {return x;}
        double imag() {return y;}
    };
    CD conj(const CD &c) {return CD(c.x, -c.y);}
    const double PI = acos(-1.0L);
    #define MAX_LEN 1000000
    int N=-1;
    int perm[MAX_LEN];
    CD wp[2][MAX_LEN];

    void precalculate(int n) {
        assert((n & (n-1)) == 0);
        N = n;
        memset(perm,0,sizeof(int)*N);
        for (int k=1; k<N; k<<=1) {
            for (int i=0; i<k; ++i) {
                perm[i] <<= 1;
                perm[i+k] = 1 + perm[i];
            }
        }
        for (int i=0; i<N; ++i) {
            wp[0][i] = CD( cos(2*PI*i/N),  sin(2*PI*i/N) );
            wp[1][i] = CD( cos(2*PI*i/N), -sin(2*PI*i/N) );
        }
    }
    void fft(vector<CD>& v,bool inv=false)
    {
        int n=v.size();
        if(n!=N)
            precalculate(n);
        for(int i=0;i<N;++i)
        {
            if(i<perm[i])
                swap(v[i],v[perm[i]]);
        }
        int d=n/2;
        for(int l=2;l<=n;l=l<<1)
        {
            for(int i=0;i<n;i+=l)
            {
                int l2=l>>1;
                for(int j=0,wi=0;j<l2;++j,wi+=d)
                {
                    CD x=v[i+j];
                    CD y=v[i+j+l2]*wp[inv][wi];
                    v[i+j]=x+y;
                    v[i+j+l2]=x-y;
                }
            }
            d/=2;
        }
        if(inv)
        {
            for(auto &e:v)
                e/=n;
        }
    }
    vector<ll> multiply(vector<ll>& a ,vector<ll>& b)
    {
        int n=1;
        while(n<a.size()+b.size())
            n=n<<1;
        vector<CD> fa(a.begin(),a.end()),fb(b.begin(),b.end());
        fa.resize(n);
        fb.resize(n);
        fft(fa);
        fft(fb);
        for(int i=0;i<n;++i)
            fa[i]=fa[i]*fb[i];
        fft(fa,true);
        vector<ll> ans(n);
        for(int i=0;i<n;++i)
            ans[i]=round(fa[i].real());
        return ans;
    }
    vector<CD> multiply(vector<CD> &a,vector<CD>& b)
    {
        int n=1;
        while(n<a.size()+b.size())
            n=n<<1;
        vector<CD> fa(a.begin(),a.end()),fb(b.begin(),b.end());
        fa.resize(n);
        fb.resize(n);
        fft(fa);
        fft(fb);
        for(int i=0;i<n;++i)
            fa[i]=fa[i]*fb[i];
        fft(fa,true);
        return fa;
    }
}
///*********************************************///
//d is the prefix sum of a={0,.....}
vll allPossibleSubSum(vll d)
{
    vll a(d.back()+1,0),b(d.back()+1,0);
    int l=d.back();
    for(auto e:d)
    {
        ++b[e];
        ++a[l-e];
    }
    vll out=fft::multiply(a,b);
    return vector<ll>(out.begin()+l,out.end());
}
