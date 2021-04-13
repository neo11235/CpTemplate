vector<int> d1;
vector<int> d2;// from i-d2[i] to i+d2[i]-1
void manacher(char* str,int n){
    d1.resize(n);
    d2.resize(n);
    int i,l=0,r=-1,k;
    for(i=0;i<n;i++){
        k=i>r?1:min(d1[l+r-i],r-i+1);
        while(0<=i-k&&i+k<n&&str[i-k]==str[i+k]){
            k++;
        }
        d1[i]=k--;
        if(i+k>r){
            l=i-k;
            r=i+k;
        }
    }
    l=0;
    r=-1;
    for(i=0;i<n;i++){
        k=i>r?0:min(d2[l+r-i+1],r-i+1);
        while(0<=i-k-1&&i+k<n&&str[i+k]==str[i-k-1]){
            k++;
        }
        d2[i]=k--;
        if(i+k>r){
            l=i-k-1;
            r=i+k;
        }
    }
}
