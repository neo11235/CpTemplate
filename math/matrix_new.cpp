#define getPos(i,j,m) ((i)*m+(j))
template<class T>
class Matrix
{
public:
    T* M=NULL;
    int n,m;
    Matrix(){n=m=0;}
    Matrix(int n,int m)
    {
        this->n=n;
        this->m=m;
        M=new T[n*m];
    }
    Matrix(int n,int m,int val)//create a matrix with main diagonal set to val,rest 0
    {
        this->n=n;
        this->m=m;
        M=new T[n*m];
        memset(M,0,sizeof(T)*n*m);
        int pos=0;
        for(int i=0;i<min(n,m);++i,pos+=m+1)
        {
            M[pos]=val;
        }
    }
    Matrix(std::initializer_list<initializer_list<T> > listdata)
    {
        n=(int)listdata.size();
        m=(int)((listdata.begin())->size());
        M=new T[n*m];
        int pos=0;
        for(int i=0;i<n;++i)
        {
            for(int j=0;j<m;++j,++pos)
            {
                M[pos]=((listdata.begin()+i)->begin())[j];
            }
        }
    }
    Matrix(const Matrix<T> & mat)
    {
        this->n=mat.n;
        this->m=mat.m;
        int len=n*m;
        M=new T[len];
        for(int i=0;i<len;++i)
            M[i]=mat.M[i];
    }
    void resize(int nn,int mm)
    {
        if(n==nn&&m==mm)
            return;
        int len=nn*mm;
        if(n*m!=len)
        {
            if(M!=NULL)
                delete[] M;
            M=new T[len];
        }
        n=nn;
        m=mm;
    }
    T* operator[](int indx)//this operation is slower than directly accessing M,if lots of accessing required then directly access M
    {
        return M+indx*m;
    }
    Matrix<T> operator=(const Matrix<T>&  mat2)
    {
        if((void*)this==(void*)&mat2)
            return *this;
        int len=mat2.n*mat2.m;
        if(n*m!=len)
        {
            if(M!=NULL)
                delete[] M;
            M=new T[len];
        }
        this->n=mat2.n;
        this->m=mat2.m;
        for(int i=0;i<len;++i)
            M[i]=mat2.M[i];
        return *this;
    }
    Matrix<T>& operator=(T val)
    {
        assert(M!=NULL);
        int len=n*m;
        for(int i=0;i<len;++i)
            M[i]=val;
        return *this;
    }
    //arithmetic operator
    Matrix<T>& operator+(const Matrix<T>& mat2)
    {
        assert(M&&mat2.M&&n==mat2.n&&m==mat2.m);
        int len=n*m;
        for(int i=0;i<len;++i)
            M[i]+=mat2.M[i];
        return *this;
    }
    Matrix<T>& operator+(T val)//honestly never used
    {
        assert(M);
        int len=n*m;
        for(int i=0;i<len;++i)
            M[i]+=val;
        return *this;
    }
    Matrix<T>& operator-(const Matrix<T>& mat2)
    {
        assert(M&&mat2.M&&n==mat2.n&&m==mat2.m);
        int len=n*m;
        for(int i=0;i<len;++i)
            M[i]-=mat2.M[i];
        return *this;
    }
    Matrix<T>& operator-(T val)
    {
        assert(M);
        int len=n*m;
        for(int i=0;i<len;++i)
            M[i]-=val;
    }
    Matrix<T> operator*(Matrix<T> const& mat2)//tested
    {
        assert(M&&mat2.M&&m==mat2.n);
        Matrix<T> res(n,mat2.m);
        int len=n*mat2.m;
        memset(res.M,0,sizeof(T)*len);
        int pos=0;
        for(int i=0;i<n;++i)
        {
            for(int j=0;j<m;++j,++pos)
            {
                T cur=M[pos];
                int pos2=j*res.m;
                int pos3=i*res.m;
                for(int k=0;k<mat2.m;++k,++pos2,++pos3)
                {
                    res.M[pos3]+=cur*mat2.M[pos2];
                    #ifdef SLOW_MOD  // if mod*mat2.M[]*m>range(T)
                    res.M[pos3]%=SLOW_MOD;
                    #endif // SLOW_MOD
                }
            }
            #ifdef FAST_MOD// if mod+mod*mat2.M[]*m<range(T)
            int pos3=i*res.m;
            for(int k=0;k<mat2.m;++k,++pos3)
                res.M[pos3]%=FAST_MOD;
            #endif // FAST_MOD
        }
        return res;

    }
    Matrix<T> operator^(unsigned long long power)//must be square matrix,binary exponentiation
    {
        assert(M&&n==m);
        Matrix<T> res(n,n,1);
        int i=63;
        for(;i>=0;--i)if((power>>i)&1)break;
        for(;i>=0;--i)
        {
            res=res*res;
            if((power>>i)&1)
                res=res*(*this);
        }
        return res;
    }
    Matrix<T> operator%(T _mod)
    {

        assert(M);
        int len=n*m;
        for(int i=0;i<len;++i)
            M[i]%=_mod;
        return *this;
    }
    ~Matrix()
    {
        if(M!=NULL)
            delete[] M;
    }

};
template<typename T>
ostream& operator<<(ostream& os,Matrix<T> const & M)
{
    int pos=0;
    for(int i=0;i<M.n;++i)
    {
        for(int j=0;j<M.m;++j,++pos)
        {
            os<<M.M[pos]<<' ';
        }
        os<<'\n';
    }
    return os;
}
template<typename T>
istream& operator>>(istream& is,Matrix<T>& M)
{
    int len=M.n*M.m;
    for(int i=0;i<len;++i)
    {
        is>>M.M[i];
    }
    return is;
}
