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
