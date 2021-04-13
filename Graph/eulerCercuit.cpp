
//assumes G is connected undirected simple Graph
vector<set<int> >  G;
vi sol;
void etour(int node)
{
    stack<int> dStack;
    dStack.push(node);
    while(!dStack.empty())
    {
        int tnode=dStack.top();
        if(G[tnode].empty())
        {
            sol.push_back(tnode);
            dStack.pop();
        }
        else{
            int v=*G[tnode].begin();
            dStack.push(v);
            G[tnode].erase(v);
            G[v].erase(tnode);
        }
    }
}
//////////directed case
vector<set<int> >  G;
vi sol;
vi indeg;
void etour(int node)
{
    stack<int> dStack;
    dStack.push(node);
    while(!dStack.empty())
    {
        int tnode=dStack.top();
        if(G[tnode].empty())
        {
            sol.push_back(tnode);
            dStack.pop();
        }
        else{
            int v=*G[tnode].begin();
            dStack.push(v);
            G[tnode].erase(G[tnode].begin());
            //G[v].erase(G[v].find(tnode));
        }
    }
    reverse(sol.begin(),sol.end());
}
