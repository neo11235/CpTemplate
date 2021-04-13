Graph G;
vi bl;
vi Color;
bool colorBfs(int s)
{
    queue<int> Q;
    Q.push(s);
    int node;
    int nc;
    Color[s]=0;
    while(!Q.empty())
    {
        node=Q.front();
        Q.pop();
        if(bl[node])
            continue;
        bl[node]=1;
        nc=Color[node]^1;
        for(auto e:G[node])
        {
            if(bl[e]||Color[e]!=-1)
            {
                if(Color[e]!=nc)
                    return false;
                continue;
            }
            Color[e]=nc;
            Q.push(e);
        }
    }
    return true;
}
bool biColor(void){
    int i;
    for(i=0;i<(int)G.size();i++)
    {
        if(!bl[i])
        {
            if(!colorBfs(i))
                return false;
        }
    }
    return true;
}
