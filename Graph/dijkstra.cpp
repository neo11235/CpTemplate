void dijkstra(vector<vector<pii > >&G,int s,vector<int>& ans,vector<int>& parent){//check for overflow
    int n=G.size();
    ans.assign(n,infi);
    parent.assign(n,-1);
    priority_queue<pii,vector<pii>,greater<pii> > pq;
    ans[s]=0;
    pq.push(mp(0,s));
    int v,d_v,to,len;
    while(!pq.empty()){
        v=pq.top().second;
        d_v=pq.top().first;
        pq.pop();
        if(d_v!=ans[v])continue;

        for(auto edge:G[v]){//<vertex,weight> pair
            to=edge.first;
            len=edge.second;
            if(ans[v]+len<ans[to]){
                ans[to]=ans[v]+len;
                parent[to]=v;
                pq.push(mp(ans[to],to));
            }
        }
    }
    return;
}
/*imp2*/
vector<vector<pii>> G;
vector<int> sp1;
vector<int> sp2;
void dijkstra(int n,int s){
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    pq.push(mp(s,0));
    pii tmp;
    while(!pq.empty()){
        tmp=pq.top();
        pq.pop();
        if(sp1[tmp.first]==tmp.second||sp2[tmp.first]==tmp.second)continue;
        if(tmp.second<sp1[tmp.first]){
            sp2[tmp.first]=sp1[tmp.first];
            sp1[tmp.first]=tmp.second;
            for(auto E:G[tmp.first]){
                pq.push(mp(E.first,E.second+sp1[tmp.first]));
                if(sp2[tmp.first]!=infi)
                    pq.push(mp(E.first,E.second+sp2[tmp.first]));
            }
        }
        else{
            if(tmp.second<sp2[tmp.first]){
                sp2[tmp.first]=tmp.second;
                for(auto E:G[tmp.first]){
                    pq.push(mp(E.first,E.second+sp2[tmp.first]));
                }
            }
        }
    }
}

//
WGraph G;
vector<ll> sol;
vi vis;
void dijkstra(int s)
{
    priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int>>> Q;
    Q.push(mp(0,s));
    ll spath;
    int node;
    while(!Q.empty())
    {
        spath=Q.top().first;
        node=Q.top().second;
        Q.pop();
        if(vis[node])
            continue;
        vis[node]=1;
        sol[node]=spath;
        for(auto e:G[node])
        {
            if(vis[e.first])
                continue;
            Q.push(mp(spath+e.second,e.first));
        }
    }
}
