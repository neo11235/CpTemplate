struct element
{
    ll sum;
    element* lft;
    element* rht;
    element()
    {
        lft=rht=NULL;
        sum=0;
    }
    element(ll s,element* llft,element* rrht)
    {
        sum=s;
        lft=llft;
        rht=rrht;
    }
};
int data[200000];
void build(element* v,int vl,int vr)
{
    if(vl==vr)
    {
        v->sum=data[vl];
        return;
    }
    int mid=(vl+vr)/2;
    v->lft=new element();
    v->rht=new element();
    build(v->lft,vl,mid);
    build(v->rht,mid+1,vr);
    v->sum=v->lft->sum+v->rht->sum;
}
ll query(element* v,int vl,int vr,int l,int r)
{
    if(vl==l&&vr==r)
    {
        return v->sum;
    }
    int mid=(vl+vr)/2;
    if(r<=mid)
    {
        return query(v->lft,vl,mid,l,r);
    }
    else if(l>mid)
    {
        return query(v->rht,mid+1,vr,l,r);
    }
    else
    {
        return query(v->lft,vl,mid,l,mid)+query(v->rht,mid+1,vr,mid+1,r);
    }
}
void update(element* vold,element* vnew,int vl,int vr,int pos,int el)
{
    if(vl==vr)
    {
        vnew->sum=el;
        return;
    }
    int mid=(vl+vr)/2;
    if(pos<=mid)
    {
        vnew->rht=vold->rht;
        vnew->lft=new element();
        update(vold->lft,vnew->lft,vl,mid,pos,el);
    }
    else
    {
        vnew->lft=vold->lft;
        vnew->rht=new element();
        update(vold->rht,vnew->rht,mid+1,vr,pos,el);
    }
    vnew->sum=vnew->lft->sum+vnew->rht->sum;
}
