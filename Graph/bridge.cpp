///basic implementation
vector<vector<int> > g;
vector<int> low;
vector<int> dis;
int timer=1;
vector<pii >bridges;
void B_dfs(int node,int p=-1){
    dis[node]=low[node]=++timer;
    for(int i:g[node]){
        if(i==p)continue;
        if(dis[i]){
            low[node]=min(low[node],dis[i]);
        }
        else{
            B_dfs(i,node);
            low[node]=min(low[node],low[i]);
            if(dis[node]<low[i]){
                bridges.push_back(mp(node,i));
            }
        }
    }
    ++timer;
}
void init()
{
    low.resize(g.size());
    dis.assign(g.size(),0);
    timer=1;
    bridges.clear();
}
///********************************************///
