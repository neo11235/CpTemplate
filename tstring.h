#ifndef TSTRING_H_INCLUDED
#define TSTRING_H_INCLUDED

void pi_function(char* str,int sz,int* pi){//prefix function
    pi[0]=0;
    int i,j;
    for(i=1;i<sz;i++){
        j=pi[i-1];
        while(j>0&&str[i]!=str[j])j=pi[j-1];
        if(str[i]==str[j])j++;
        pi[i]=j;
    }
    return;
}
void z_function(char* str,int sz,int* z){
    z[0]=1;
    int i,l=0,r=0,j,k;
    for(i=1;i<sz;i++){
        z[i]=0;
        if(i<=r){
            z[i]=min(r-i+1,z[i-l]);
        }
        while(i+z[i]<sz&&str[z[i]]==str[i+z[i]])z[i]++;
        if(i+z[i]-1>r){
            l=i;
            r=i+z[i]-1;
        }
    }
    return;
}
/**************hashing************************/
ll *hash_;
ll p=157;
ll mod=1000002937;
void hash__(void){
    hash_[0]=(ll)(t[0]-'a'+1);
    ll tp=1;
    for(int i=1;i<m;i++){
        tp*=p;
        tp%=mod;
        hash_[i]=(hash_[i-1]+(ll)(t[i]-'a'+1)*tp)%mod;
    }
}
int hash__(char* str,int sz,ll p=157,ll mod=1000002937){
    ll rval=(ll)(str[0]-'a'+1);
    ll tp=1;
    for(int i=1;i<sz;i++){
        tp*=p;
        tp%=mod;
        rval=(rval+(ll)(str[i]-'a'+1)*tp)%mod;
    }
    return (int)rval;
}
/***************************/

#endif // TSTRING_H_INCLUDED
