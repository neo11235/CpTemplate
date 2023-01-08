#define max_number 100005
struct Dpriority_queue{
public:
    priority_queue<int,vector<int>,greater<int> > Q;
    int cnt[max_number];
    int inside[max_number];
    Dpriority_queue()
    {
        memset(cnt,0,sizeof(cnt));
        memset(inside,0,sizeof(inside));

    }
    void push(int x)
    {
        if(!inside[x]){
            Q.push(x);
            inside[x]=1;
        }
        ++cnt[x];
    }
    int top()
    {
        while(!Q.empty()&&cnt[Q.top()]<=0){
            inside[Q.top()]=0;
            Q.pop();
        }
        assert(!Q.empty());
        return Q.top();
    }
    void pop()
    {
        while(cnt[Q.top()]<=0)
            Q.pop();
        --cnt[Q.top()];
    }
    void erase(int val)
    {
        --cnt[val];
    }
};
