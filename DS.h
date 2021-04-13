#ifndef DS_H_INCLUDED
#define DS_H_INCLUDED

/**********************************************/
int leader[50001],pop_[50001];
int leader_(int v){
    while(leader[v]!=v){
        v=leader[v];
    }
    return v;
}
void merge_(int v,int u){
    int vl,ul;
    vl=leader_(v);
    ul=leader_(u);
    if(vl==ul)return;
    if(pop_[vl]<pop_[ul]){
        leader[vl]=ul;
        pop_[ul]+=pop_[vl];
    }
    else if(pop_[vl]>pop_[ul]){
        leader[ul]=vl;
        pop_[vl]+=pop_[ul];
    }
    else{
        leader[vl]=ul;
        pop_[ul]+=pop_[vl];
    }

}
bool if_same(int v,int u){
    return leader_(v)==leader_(u);
}
/***********************************************/

#endif // DS_H_INCLUDED
