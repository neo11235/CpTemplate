#ifndef PRIME_H_INCLUDED
#define PRIME_H_INCLUDED
bool is_prime(int64_t n){
    if(n<2)return 0;
    double sq=sqrt((double)n);
    int64_t l=(int64_t)sq,i;
    for(i=2;i<=l;i++){
        if((n%i)==0)return 0;
    }
    return 1;
}
bool is_prime(int n){
    if(n<2)return 0;
    double sq=sqrt((double)n);
    int l=(int)sq;
    int i;
    for(i=2;i<=l;i++){
        if((n%i)==0)return false;
    }
    return true;
}
int fill_p_q(int64_t n,int64_t* pfactor,int* power){
    if(n<2)return 0;
    double sq=sqrt((double)n);
    int64_t l=(int64_t)sq,i;
    int j=0;
    for(i=2;i<=l;i++){
    if((n%i)==0){
        pfactor[j]=i;
        power[j]=0;
        while((n%i)==0){
            n/=i;
            power[j]++;
        }
        j++;
    }
    }
    if(n!=1){
        power[j]=1;
        pfactor[j]=n;
        j++;
    }
    return j;
}
int fill_p_q(int n,int* pfactor,int* power){
    if(n<2)return 0;
    double sq=sqrt((double)n);
    int l=(int)sq,i;
    int j=0;
    for(i=2;i<=l;i++){
    if((n%i)==0){
        pfactor[j]=i;
        power[j]=0;
        while((n%i)==0){
            n/=i;
            power[j]++;
        }
        j++;
    }
    }
    if(n!=1){
        power[j]=1;
        pfactor[j]=n;
        j++;
    }
    return j;
}
#endif // PRIME_H_INCLUDED
