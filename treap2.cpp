
/***implicit treap****/
#include <bits/stdc++.h>
#include <random>
#include <chrono>
using namespace std;
#define sci1(a) scanf("%d",&a)
#define sci2(a,b) scanf("%d %d",&a,&b)
#define sci3(a,b,c) scanf("%d %d %d",&a,&b,&c)
#define scs(s) scanf("%s",s)
#ifndef GET_MACRO

#define GET_MACRO(__1,__2,__3,NAME,...) NAME

#endif // GET_MACRO

#define sci(...) GET_MACRO(__VA_ARGS__,sci3,sci2,sci1)(__VA_ARGS__)
#define ll long long
#define pii pair<int,int>
#define mp(a,b) make_pair(a,b)
#define LSB(i) ((i)&(-i))
#define read freopen("input.txt","r",stdin)
#define write freopen("output.txt","w",stdout)
#define infl 0x7ffffffffffffff
#define infi  0x7fffffff
#define fill_(a,b) fill(a.begin(),a.end(),b)
#define pb push_back
#define xx first
#define yy second
/********************random generator********/
unsigned seed = chrono::system_clock::now().time_since_epoch().count();
linear_congruential_engine<uint_fast32_t, 1002517UL, 1001593UL, 2147483647UL> lcg(seed);
mt19937 rng(seed);
unordered_set<int> hsh;
/*************************/
struct solution{
    int sol;
    int l;
    int r;
    int sum;
    solution(){
        sol=l=r=sum=0;
    }
    solution(int val){
        sol=l=r=sum=val;
    }
};
struct node{
    int prior;
    int ssz;//subtree size;
    int val;
    solution S;
    node* l;
    node* r;
    node(){
        l=r=NULL;
    }
    node(int val,int prior){
        this->val=val;
        this->prior=prior;
        this->ssz=1;
        l=r=NULL;
    }
};
typedef node* pnode;
void merge(solution& out,solution l,solution r){
    out.sol=max(max(l.sol,r.sol),l.r+r.l);
    out.sum=l.sum+r.sum;
    out.l=max(l.l,l.sum+r.l);
    out.r=max(r.r,r.sum+l.r);
    return;
}
#define get_key(root) (root?((root->l?root->l->ssz:0)+1):0)
#define get_size(root) (root?root->ssz:0)
void build_sol(pnode root){
    if(!root)return;
    root->S.l=root->S.r=root->S.sol=root->S.sum=root->val;
    if(root->l)
        merge(root->S,root->l->S,root->S);
    if(root->r)
        merge(root->S,root->S,root->r->S);

    root->ssz=(root->l?root->l->ssz:0)+(root->r?root->r->ssz:0)+1;
    return;
}

void merge(pnode& root,pnode l,pnode r){
    if(!l||!r){
        root=l?l:r;
        return;
    }
    else if(l->prior<r->prior){
        root=l;
        merge(l->r,l->r,r);
    }
    else{
        root=r;
        merge(r->l,l,r->l);
    }
    build_sol(root);
}

void split(pnode root,int rkey,int key,pnode& l,pnode& r){
    if(!root){
        l=r=NULL;
        return;
    }
    else if(rkey<=key){
        l=root;
        split(root->r,rkey+get_key(root->r),key,l->r,r);
    }
    else{
        r=root;
        split(root->l,rkey-(get_key(root)-get_key(root->l)),key,l,r->l);
    }
    build_sol(l);
    build_sol(r);
}
void insert(pnode& root,pnode el,int elkey,int rkey){
    if(!root){
        root=el;
    }
    else if(root->prior>el->prior){
        split(root,rkey,elkey,el->l,el->r);
        root=el;
    }
    else{
         if(rkey<=elkey){
            insert(root->r,el,elkey,rkey+get_key(root->r));
         }
         else{
            insert(root->l,el,elkey,rkey-(get_key(root)-get_key(root->l)));
         }
    }
    build_sol(root);
}
int get_random_priority(){
    while(1){
        int out=lcg();
        if(hsh.find(out)==hsh.end()){
            hsh.insert(out);
            return out;
        }
    }
}
void insert(pnode& root,int pos,int val){
    pnode el=new node(val,get_random_priority());
    build_sol(el);
    insert(root,el,pos,get_key(root));
}
void erase(pnode& root,int key,int rkey){
    //if(!root)return;
    if(key==rkey){
        merge(root,root->l,root->r);
    }
    else if(rkey<key){
        erase(root->r,key,rkey+get_key(root->r));
    }
    else{
        erase(root->l,key,rkey-(get_key(root)-get_key(root->l)));
    }
    build_sol(root);
}
void print_tree(pnode root,int depth=0){
    if(root==NULL)return;


    printf("(%d %d %d)",root->val,depth,root->ssz);

    if(root->l!=NULL){
        printf("l(");
        print_tree(root->l,depth+1);
        printf(")");
    }
    printf("  ");
    if(root->r!=NULL){
        printf("r(");
        print_tree(root->r,depth+1);
        printf(")");
    }
}
void print_sort(pnode root){
    if(!root)return;
    if(root->l)
        print_sort(root->l);
    printf("%d ",root->val);
    if(root->r)
        print_sort(root->r);
}
solution query(pnode v,int rkey,int vl,int vr,int l,int r){
    if(vl>vr||v==NULL||l<vl||r>vr||l>r)return solution(0);
    if(vl==l&&vr==r){
        return v->S;
    }
    int mid=vl+get_size(v->l)-1;
    if(r<=mid)return query(v->l,rkey-(get_key(v)-get_key(v->l)),vl,mid,l,r);
    else if(l>(mid+1))
        return query(v->r,rkey+get_key(v->r),mid+2,vr,l,r);
    else{
        solution S(v->val);
        solution tmp;
        if(l<=mid){
            tmp=query(v->l,rkey-(get_key(v)-get_key(v->l)),vl,mid,l,mid);
            merge(S,tmp,S);
        }
        if(r>(mid+1)){
            tmp=query(v->r,rkey+get_key(v->r),mid+2,vr,mid+2,r);
            merge(S,S,tmp);
        }
        return S;
    }
}
int main(){
    int n,q,tmp,i;
    sci(n);
    pnode root=NULL;
    for(i=0;i<n;i++){
        sci(tmp);
        insert(root,i+1,tmp);
    }
    sci(q);
    char id[10];
    int x,y;
    for(i=0;i<q;i++){
        scanf("%s",id);
        if(id[0]=='I'){

            sci(x,y);
            insert(root,x-1,y);
        }
        else if(id[0]=='Q'){
            sci(x,y);
            printf("%d\n",query(root,get_key(root),1,get_size(root),x,y).sol);
            //print_tree(root);
            //cout<<endl;
        }
        else if(id[0]=='R'){
            sci(x,y);
            erase(root,x,get_key(root));
            insert(root,x-1,y);
        }
        else{
            sci(x);
            erase(root,x,get_key(root));
        }
        //print_sort(root);
        //cout<<endl;
        //cout<<endl;

    }
    return 0;
}
