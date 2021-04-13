int nxt_permutation(int* in,int sz){
    int i=sz-1;
    int tmp1,pivot,swp;
    tmp1=in[i];
    i=sz-2;
    for(;i>=0;i--){
        if(tmp1>in[i]){
            break;
        }
        else{
            tmp1=in[i];
        }
    }
    if(i==-1){
        return 0;
    }
    pivot=i;
    i=sz-1;
    for(;i>=0;i--){
        if(in[i]>in[pivot]){
            break;
        }
    }
    swp=in[i];
    in[i]=in[pivot];
    in[pivot]=swp;
    _reverse((in+pivot+1),(sz-pivot-1));
    return 1;
}
