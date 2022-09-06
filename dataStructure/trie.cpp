//change to oop later
const int symbolSize=2;
struct vertex
{
    bool leaf=false;
    int next[symbolSize];
    vertex()
    {
        next[0]=next[1]=0;
    }
};
#define MX_SIZE 20000000
vector<vertex> trie(MX_SIZE);
int curSize=1;
void addNumber(int x)
{
    int curVertex=0;
    for(int i=30;i>=0;i--)
    {
        if(x&(1<<i))
        {
            if(!trie[curVertex].next[1])
            {
                trie[curVertex].next[1]=curSize++;
            }
            curVertex=trie[curVertex].next[1];
        }
        else
        {
            if(!trie[curVertex].next[0])
            {
                trie[curVertex].next[0]=curSize++;
            }
            curVertex=trie[curVertex].next[0];
        }
    }
    trie[curVertex].leaf=true;
}

/********Basic Trie*************/
//also write for adding integer to trie
template<int MAX_SIZE,int AS=26>
struct Trie
{
    struct Node
    {
        int nxt[AS];
        bool leaf;
        Node(){
            leaf=false;
            memset(nxt,-1,sizeof(int)*AS);
        }
    };
    Node trie[MAX_SIZE];
    int curSize=1;
    bool addString(string const& s)
    {
        int cur=0;
        bool res=false;
        bool r2=true;
        for(auto e:s)
        {
            e-='0';
            if(trie[cur].nxt[e]==-1)
            {
                res=true;
                trie[cur].nxt[e]=curSize++;
            }
            if(trie[cur].leaf)
                r2=false;
            cur=trie[cur].nxt[e];
        }
        trie[cur].leaf=true;
        return res&&r2;
    }
};
