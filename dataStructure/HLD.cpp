namespace HLD{
    template<class T>
    class SegTree// point update range query
    {
    public:
        T* sgt;
        int n;
        T (*combine)(T,T);
        SegTree(T (*combine)(T,T),int sz)
        {
            n=sz;
            sgt=new T[4*sz];
            memset(sgt,0,sizeof(T)*4*sz);
            this->combine=combine;
        }
        SegTree(T (*combine)(T,T),T* data,int sz)
        {
            n=sz;
            sgt=new T[4*sz];
            this->combine=combine;
            build(data,1,0,n-1);
        }

        void build(T* data,int v,int vl,int vr)
        {
            if(vl==vr)
            {
                sgt[v]=data[vl];
                return;
            }
            int mid=(vl+vr)/2;
            build(data,2*v,vl,mid);
            build(data,2*v+1,mid+1,vr);
            sgt[v]=combine(sgt[2*v],sgt[2*v+1]);
        }
        void build(vector<T>& data,int v,int vl,int vr)
        {
            if(vl==vr)
            {
                sgt[v]=data[vl];
                return;
            }
            int mid=(vl+vr)/2;
            build(data,2*v,vl,mid);
            build(data,2*v+1,mid+1,vr);
            sgt[v]=combine(sgt[2*v],sgt[2*v+1]);
        }
        void update(int v,int vl,int vr,int pos,T el)
        {
            if(vl==vr)
            {
                sgt[v]=el;
                return;
            }
            int mid=(vl+vr)/2;
            if(pos<=mid)
                update(2*v,vl,mid,pos,el);
            else
                update(2*v+1,mid+1,vr,pos,el);
            sgt[v]=combine(sgt[2*v],sgt[2*v+1]);
        }
        void update(int pos,T el)
        {
            update(1,0,n-1,pos,el);
        }
        T query(int v,int vl,int vr,int l,int r)
        {
            if(vl==l&&vr==r)
                return sgt[v];
            int mid=(vl+vr)/2;
            if(r<=mid)
                return query(2*v,vl,mid,l,r);
            else if(l>mid)
                return query(2*v+1,mid+1,vr,l,r);
            else
                return combine(query(2*v,vl,mid,l,mid),query(2*v+1,mid+1,vr,mid+1,r));
        }
        T query(int l,int r)
        {
            if(l>r)
                return (T)INT_MIN;
            return query(1,0,n-1,l,r);
        }
    };
    inline int combine(int a,int b)
    {
        return max(a,b);
    }
    #define MAX_SIZE 100001
    vector<vector<int> >G;
    vector<int> parent,depth,heavy,head,pos;
    vector<int> node_val;
    vector<int> node_val_order;
    SegTree<int> sgt(combine,MAX_SIZE);
    int cur_pos;
    int dfs(int node){
        int sz=1;
        int max_c_size=0;
        for(auto c:G[node]){
            if(c!=parent[node]){
                parent[c]=node;
                depth[c]=depth[node]+1;
                int c_size=dfs(c);
                sz+=c_size;
                if(c_size>max_c_size){
                    max_c_size=c_size;
                    heavy[node]=c;
                }
            }
        }
        return sz;
    }
    void decompose(int node,int h){
        pos[node]=cur_pos++;
        head[node]=h;
        if(heavy[node]!=-1)
            decompose(heavy[node],h);
        for(int c:G[node]){
            if(c!=parent[node]&&c!=heavy[node])
                decompose(c,c);
        }
        return;
    }
    //for query on path the node_val of a node is the cost of the edge to parent
    //exclude=true for query on path,it excludes the value stored in lca(a,b)
    int query(int a,int b,int n,bool exclude=false){//n number of node in the tree
        int res=0;//not really generalized,for min max update accordingly
        while(head[a]!=head[b]){
            if(depth[head[a]]>depth[head[b]])swap(a,b);
            res=combine(res,sgt.query(pos[head[b]],pos[b]));
            b=parent[head[b]];
        }
        if(depth[a]>depth[b])swap(a,b);
        res=combine(res,exclude?sgt.query(pos[a]+1,pos[b]):sgt.query(pos[a],pos[b]));
        return res;
    }
    void update(int node,int val)
    {
        sgt.update(pos[node],val);
    }
    void init(int n){
        parent.resize(n);
        depth.resize(n);
        heavy.assign(n,-1);
        head.resize(n);
        pos.resize(n);

        parent[0]=0;//might change later
        dfs(0);
        cur_pos=0;
        decompose(0,0);

        node_val_order.resize(n);
        for(int i=0;i<n;++i)
        {
            node_val_order[pos[i]]=node_val[i];
        }
        sgt.n=n;
        sgt.build(node_val_order,1,0,n-1);
    }
}
