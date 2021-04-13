#include <bits/stdc++.h>
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
struct node{
    int key;
    int prior;
    node* left;
    node* right;
    node(){
        left=right=NULL;
    }
    node(int key,int prior){
        this->key=key;
        this->prior=prior;
        left=right=NULL;
    }
};
typedef node* pnode;

void split(pnode root,int key,pnode& l,pnode& r){
    if(root==NULL){
        l=r=NULL;
    }
    else if(root->key<=key){
        l=root;
        split(root->right,key,l->right,r);
    }
    else{
        r=root;
        split(root->left,key,l,r->left);
    }
}
void merge(pnode& root,pnode l,pnode r){
    if(!l||!r){
        root=l?l:r;
    }
    else if(l->prior<r->prior){
        root=l;
        merge(l->right,l->right,r);
    }
    else{
        root=r;
        merge(r->left,l,r->left);
    }
}
void print_tree(pnode root,int depth=0){
    if(root==NULL)return;


    printf("(%d %d)",root->key,depth);

    if(root->left!=NULL){
        printf("l(");
        print_tree(root->left,depth+1);
        printf(")");
    }
    printf("  ");
    if(root->right!=NULL){
        printf("r(");
        print_tree(root->right,depth+1);
        printf(")");
    }
}
void insert(pnode &root,pnode el){
    if(!root){
        root=el;
    }
    else if(root->prior>el->prior){
        split(root,el->key,el->left,el->right);
        root=el;
    }
    else{
        insert(root->key<el->key?root->right:root->left,el);
    }
}
void erase(pnode& root,int key){
    if(root->key==key){
        merge(root,root->left,root->right);
    }
    else{
        erase(root->key<key?root->right:root->left,key);
    }
}
void insert(pnode& root,int key){
    insert(root,new node(key,rand()%(1<<30)));
}
int main(){
    pnode tree=NULL;
    int i=10;
    for(int i=0;i<10;i++){
        insert(tree,i);
    }
    print_tree(tree);
    erase(tree,5);
    cout<<endl;
    print_tree(tree);
    return 0;
}
