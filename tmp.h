#ifndef TMP_H_INCLUDED
#define TMP_H_INCLUDED


/***************construction of trie*********/
const int K=26;
struct Vertex{
    int next[K];
    bool leaf;
    Vertex(){
        leaf=false;
        fill(begin(next),end(next),-1);
    }
};
vector<Vertex> trie(1);
void add_string(char* str,int sz){
    int v=0,i,c;
    for(i=0;i<sz;i++){
        c=(int)(str[i]-'a');
        if(trie[v].next[c]==-1){
            trie[v].next[c]=trie.size();
            trie.emplace_back();
        }
        v=trie[v].next[c];
    }
    trie[v].leaf=true;
}
/********************/
/******aho corasick**************/
const int K=26;
struct Vertex{
    int next[K];
    bool leaf=false;
    int p=-1;
    int id=-1;
    int elink=-1;
    char pch;
    int link=-1;
    int go[K];
    Vertex(int p=-1,char ch='$'):p(p),pch(ch){
        memset(next,-1,sizeof(int)*K);
        memset(go,-1,sizeof(int)*K);
    }

};
vector<int> ans;
vector<int> dup;
vector<Vertex> trie(1);
void add_string(char* str,int id){
    int v=0,i,c;
    while(*str){
        c=(int)(*str-'a');
        if(trie[v].next[c]==-1){
            trie[v].next[c]=trie.size();
            trie.emplace_back(v,*str);
        }
        v=trie[v].next[c];
        str++;
    }
    if(trie[v].leaf){
        dup[id]=trie[v].id;
    }
    else{
        trie[v].leaf=true;
        trie[v].id=id;
    }
    return;
}
int go(int v,char ch);
int get_link(int v){
    if(trie[v].link==-1){
        if(v==0||trie[v].p==0){
            trie[v].link=0;
        }
        else{
            trie[v].link=go(get_link(trie[v].p),trie[v].pch);
        }
    }
    return trie[v].link;
}
int go(int v,char ch){
    int c=(int)(ch-'a');
    if(trie[v].go[c]==-1){
        if(trie[v].next[c]!=-1){
            trie[v].go[c]=trie[v].next[c];
        }
        else{
            trie[v].go[c]=v==0?0:go(get_link(v),ch);
        }
    }
    return trie[v].go[c];
}
void aho_korasik(char* str){
    int v=0,v1,v2;
    while(*str!='\0'){
        v=go(v,*str);
        v1=v;
        while(v1){
            if(trie[v1].elink==-1){
                v2=v1;
                while(v2=get_link(v2)){
                    if(trie[v2].leaf)break;
                }
                trie[v1].elink=v2;
                v1=v2;
                if(trie[v1].leaf){
                    ans[trie[v1].id]++;
                }
            }
            else{
                v1=trie[v1].elink;
                if(trie[v1].leaf){
                    ans[trie[v1].id]++;
                }
            }
        }
        if(trie[v].leaf){
            ans[trie[v].id]++;
        }
        str++;
    }
    return;
}

#endif // TMP_H_INCLUDED
