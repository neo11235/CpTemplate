#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
template<class T>class matrix{
public:
    T** mat;
    int n,m;
    matrix();
    matrix(int nn,int mm);//creates null matrix of size nn*mm
    matrix(int nn,int mm,T val);//Create val*I matrix
    matrix(int nn,int mm,T** data);//create matrix of size nn*mm and initialize with data
    matrix(matrix<T> & mt);
    void assign(T** data);
    void assign(T val);//assign val to all element to m
    void resize(int,int);
    void operator=(const matrix<T>&);
    matrix<T> operator+(const matrix<T>&);
    matrix<T> operator*(const matrix<T>&);
    void show(void);
    ~matrix();
};
template<class T> void matrix<T>::assign(T val){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)mat[i][j]=val;
    }
    return;
}
template<class T> void matrix<T>::resize(int nn,int mm){//might change its behavior to preserve previous data later
    int i;
    for(i=0;i<n;i++){
        delete[] mat[i];
    }
    if(mat!=NULL)delete[] mat;
    mat=new T*[nn];
    for(i=0;i<nn;i++)mat[i]=new T[mm];
    n=nn;
    m=mm;
    return;
}
template<class T> matrix<T>::matrix(int nn,int mm,T val){
    mat=new T*[nn];
    for(int i=0;i<nn;i++){
        mat[i]=new T[mm];
        memset(mat[i],0,sizeof(T)*mm);
        mat[i][i]=val;
    }
    n=nn;
    m=mm;
}
template<class T> matrix<T>::matrix(){
    mat=NULL;
    n=m=0;
}
template<class T> matrix<T>::matrix(int nn,int mm){
    mat=new T*[nn];
    for(int i=0;i<nn;i++){
        mat[i]=new T[mm];
        memset(mat[i],0,sizeof(T)*mm);
    }
    n=nn;
    m=mm;
}
template<class T> matrix<T>::matrix(int nn,int mm,T** data){
    mat=new T*[nn];
    for(int i=0;i<nn;i++){
        mat[i]=new T[mm];
        for(int j=0;j<mm;j++){
            mat[i][j]=data[i][j];
        }
    }
    n=nn;
    m=mm;
}
template<class T> matrix<T>::matrix(matrix<T>& mt){
    int i,j;
    if(n!=mt.n||m!=mt.m){
        mat=new T*[mt.n];
        for(i=0;i<n;i++)mat[i]=new T[mt.m];
        n=mt.n;
        m=mt.m;
    }
    for(i=0;i<n;i++){
        for(j=0;j<m;j++)mat[i][j]=mt.mat[i][j];
    }
}
template<class T> matrix<T>::~matrix(){
    for(int i=0;i<n;i++){
        delete[] mat[i];
    }
    if(n!=0)delete[] mat;
}
template<class T>void matrix<T>::show(void){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)cout<<mat[i][j]<<" ";
        printf("\n");
    }
}
template<class T> void matrix<T>::assign(T**data){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)mat[i][j]=data[i][j];
    }
    return;
}
template<class T>void matrix<T>::operator=(const matrix<T> &mat2){
    int i,j;
    if(n!=mat2.n||m!=mat2.m){
        for(i=0;i<n;i++){
            delete[] mat[i];
        }
        if(mat!=NULL)delete[] mat;
        n=mat2.n;
        m=mat2.m;
        mat=new T*[n];
        for(i=0;i<n;i++){
            mat[i]=new T[m];
        }
    }
    for(i=0;i<n;i++){
        for(j=0;j<m;j++)mat[i][j]=mat2.mat[i][j];
    }
    return;
}
template<class T>matrix<T> matrix<T>::operator+(const matrix<T> &mat2){
    matrix<T> res(n,m,mat);
    if(n!=mat2.n||m!=mat2.m){
        cout<<"Incompatible matrix"<<endl;//later substitute this with exception throw
        return res;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)res.mat[i][j]+=mat2.mat[i][j];
    }
    return res;
}
template<class T>matrix<T> matrix<T>::operator*(const matrix<T> &mat2){
    matrix<T> res(n,mat2.m,(T)0);//need fixing,its a bug should be res(n,mat2.m,(T)0)
    if(m!=mat2.n){
        cout<<"Incompatible matrix"<<endl;//later substitute this with exception throw
        return res;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<mat2.m;j++){
            for(int k=0;k<m;k++)res.mat[i][j]+=mat[i][k]*mat2.mat[k][j];
        }
    }
    return res;
}
/***********related function**************/
template<class T> matrix<T> bin_exp(matrix<T> &m,unsigned long long n){//must be square matrix
    int i;
    for(i=63;i>=0;i--)if((n>>i)&1)break;
    matrix<T> res(m.m,m.m,1);
    for(;i>=0;i--){
        res=res*res;
        if((n>>i)&1)res=res*m;
    }
    return res;
}
template<class T>matrix<T> modular_exp(matrix<T>& m,unsigned long long n,T mod){
    int i,j,k;
    for(i=63;i>=0;i--)if((n>>i)&1)break;
    matrix<T> res(m.m,m.m,1);
    for(;i>=0;i--){
        res=res*res;
        if((n>>i)&1)res=res*m;
        for(j=0;j<res.n;j++){
            for(k=0;k<res.m;k++)res.mat[j][k]%=mod;
        }
    }
    return res;
}
double pres=1E-9;
int SLAE(matrix<double>& mat){//m must be n*(n+1) A*x=c format
    int i,j,k,id1,id2;
    double tmp1,tmp2,mx;
    for(i=0;i<mat.n;i++){
        id1=i;
        mx=abs(mat.mat[i][i]);
        for(j=i+1;j<mat.n;j++){
            if(abs(mat.mat[j][i])>mx){
                mx=abs(mat.mat[j][i]);
                id1=j;
            }
        }
        swap(mat.mat[i],mat.mat[id1]);
        if(abs(mat.mat[i][i])<pres)return -1;//infinite solution exist
        for(j=i+1;j<mat.m;j++){
            mat.mat[i][j]/=mat.mat[i][i];
        }
        mat.mat[i][i]=1.0;
        for(j=0;j<mat.n;j++){
            if(j==i||abs(mat.mat[j][i])<pres)continue;
            for(k=i+1;k<mat.m;k++){
                mat.mat[j][k]-=mat.mat[i][k]*mat.mat[j][i];
            }
            mat.mat[j][i]=0.0;
        }
    }
    return 0;
}
//double pres=1E-9;
template<class T>//not fully tested
int SLAE1(matrix<T>& mat){//m must be n*(n+1) A*x=c format T must be double float or complex<double/float> type
    int i,j,k,id1,id2;
    double tmp1,tmp2,mx;
    for(i=0;i<mat.n;i++){
        id1=i;
        mx=abs(mat.mat[i][i]);
        for(j=i+1;j<mat.n;j++){
            if(abs(mat.mat[j][i])>mx){
                mx=abs(mat.mat[j][i]);
                id1=j;
            }
        }
        swap(mat.mat[i],mat.mat[id1]);
        if(abs(mat.mat[i][i])<pres)return -1;
        for(j=i+1;j<mat.m;j++){
            mat.mat[i][j]/=mat.mat[i][i];
        }
        mat.mat[i][i]=(T)1.0;
        for(j=0;j<mat.n;j++){
            if(j==i||abs(mat.mat[j][i])<pres)continue;
            for(k=i+1;k<mat.m;k++){
                mat.mat[j][k]-=mat.mat[i][k]*mat.mat[j][i];
            }
            mat.mat[j][i]=(T)0.0;
        }
    }
    return 0;
}
template<class T> T det(matrix<T> &mat){

}

#endif // MATRIX_H_INCLUDED
