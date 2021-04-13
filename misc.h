#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED
/******need to write generalized MO algorithm
int main(){
    int t,n,q,i,j,k,l,r,*data,*bl,block_size=500,cs,cur_l,cur_r;
        bl=new int[1000001];
        data=new int[200000];
        ll *ans,tans;
        ans=new ll[200000];
        vector<pair<pair<int,int>,int > > vct;
        vector<pair<int,int> > query;
        sci(n,q);

        vct.resize(q);
        query.resize(q);

        for(i=0;i<n;i++)sci(data[i]);

        for(i=0;i<q;i++){
            sci(l,r);l--;r--;
            query[i]=mp(l,r);
            vct[i]=mp(mp(l/block_size,r),i);
        }
        sort(vct.begin(),vct.end());

        cur_l=0;
        cur_r=-1;
        tans=0;
        memset(bl,0,sizeof(int)*1000001);

        for(i=0;i<q;i++){
            j=vct[i].yy;
            while(cur_l>query[j].xx){
                cur_l--;
                tans+=(ll)data[cur_l]*(2ll*(ll)(bl[data[cur_l]])+1ll);
                bl[data[cur_l]]++;
            }
            while(cur_r<query[j].yy){
                cur_r++;
                tans+=(ll)data[cur_r]*(2ll*(ll)(bl[data[cur_r]])+1ll);
                bl[data[cur_r]]++;
            }
            while(cur_l<query[j].xx){
                tans-=(ll)data[cur_l]*(2ll*(ll)(bl[data[cur_l]])-1ll);
                bl[data[cur_l]]--;
                cur_l++;
            }
            while(cur_r>query[j].yy){
                tans-=(ll)data[cur_r]*(2ll*(ll)(bl[data[cur_r]])-1ll);
                bl[data[cur_r]]--;
                cur_r--;
            }
            ans[j]=tans;
        }
        for(i=0;i<q;i++){
            printf("%I64d\n",ans[i]);
        }

    return 0;
}
***/

/*******************important piece of code****************************/
int b_search_inc(int* data,int _sz,int el){
    if(_sz==0)return 0;
    if(_sz==1){
        if(data[0]<=el)return 1;
        return 0;
    }
    int l=_sz/2,r=_sz-l;
    if(data[l-1]<=el){
        return l+b_search_inc(data+l,r,el);
    }
    else{
        return b_search_inc(data,l,el);
    }
}
int b_search_exc(int* data,int _sz,int el){
    if(_sz==0)return 0;
    if(_sz==1){
        if(data[0]<el)return 1;
        return 0;
    }
    int l=_sz/2,r=_sz-l;
    if(data[l-1]<el){
        return l+b_search_exc(data+l,r,el);
    }
    else{
        return b_search_exc(data,l,el);
    }
}
/*********************************************************************/
int b_search(vector<int>& vct,int el){
    if(vct.size()==0)return 0;
    int l=0;
    int r=vct.size()-1,mid;
    while(l<r){
        mid=(l+r)/2;
        if(vct[mid]<el){
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    if(vct[l]<el)return l+1;
    return l;
}
#endif // MISC_H_INCLUDED
