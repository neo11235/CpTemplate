//first implementation
//author: Hasanul Islam
//date: 11/9/2022
namespace SuffixAut{
    const int AS=26;//alphabet size
    const int offset='A';
    const int MaxNode=300000;
    struct SNode{
        int nxt[AS];
        int sufLink;
        int len;
        int terminal=false;
        SNode(){
            memset(nxt,-1,sizeof(nxt));
            sufLink=-1;
            len=0;
        }
        void clear()
        {
            memset(nxt,-1,sizeof(nxt));
            sufLink=-1;
            len=0;
            terminal=false;
        }
    };
    SNode nodes[MaxNode];
    int curNode=1;
    int lastNode=0;
    void init()
    {
        for(int i=0;i<curNode;++i)
        {
            nodes[i].clear();
        }
        curNode=1;
        lastNode=0;
    }
    void markTerminal(int val=true)
    {
        int lst=lastNode;
        while(lst!=-1)
        {
            nodes[lst].terminal=val;
            lst=nodes[lst].sufLink;
        }
    }
    void extend(char c)
    {

        int lst=lastNode;
        int newNode=lastNode=curNode++;
        nodes[newNode].len=nodes[lst].len+1;
        c-=offset;
        while(lst!=-1)
        {
            if(nodes[lst].nxt[c]==-1)
                nodes[lst].nxt[c]=newNode;
            else
                break;
            lst=nodes[lst].sufLink;
        }
        if(lst==-1)
        {
            nodes[newNode].sufLink=0;
            return;
        }
        int p=lst,q=nodes[lst].nxt[c];
        if(nodes[p].len+1==nodes[q].len)
        {
            nodes[newNode].sufLink=q;
            return;
        }
        int clone=curNode++;
        nodes[clone]=nodes[q];
        nodes[clone].len=nodes[p].len+1;
        nodes[newNode].sufLink=clone;
        nodes[q].sufLink=clone;
        while(p!=-1)
        {
            if(nodes[p].nxt[c]==q)
                nodes[p].nxt[c]=clone;
            else
                break;
            p=nodes[p].sufLink;
        }
    }
    void build(string s)
    {
        init();
        for(auto e:s)
            extend(e);
        markTerminal();
    }
    void print()
    {
        for(int i=0;i<curNode;++i)
        {
            cout<<"Node "<<i<<":\n";
            for(int j=0;j<AS;++j)
            {
                if(nodes[i].nxt[j]!=-1)
                {
                    cout<<(char)(j+offset)<<':'<<nodes[i].nxt[j]<<'\n';
                }
            }
            cout<<"len "<<nodes[i].len<<'\n';
            cout<<"sufLink "<<nodes[i].sufLink<<'\n';
            cout<<"terminal "<<nodes[i].terminal<<'\n';
        }
    }
}
