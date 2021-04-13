char data[2000][2001];
int largest_zero_sub(int n,int m){
    int i,j;
    int mx=0;
    vector<int> d(m,-1);
    vector<int> tans(m,0);
    int k;
    for(i=0;i<n;i++){
        stack<pii> st;
        st.push(mp(-1,2000));
        for(j=0;j<m;j++){
            if(data[i][j]=='0'){
                while(st.top().second<=d[j])st.pop();
                tans[j]+=(i-d[j])*(j-st.top().first);
            }
            else{
                d[j]=i;
                while(st.size()>1)st.pop();
            }
            st.push(mp(j,d[j]));
        }
        while(!st.empty())st.pop();
        st.push(mp(m,2000));
        for(j=m-1;j>=0;j--){
            if(data[i][j]=='0'){
                while(st.top().second<=d[j])st.pop();
                tans[j]+=(i-d[j])*(st.top().first-j-1);
            }
            else{
                while(st.size()>1)st.pop();
            }
            st.push(mp(j,d[j]));
        }
        mx=max(mx,*max_element(tans.begin(),tans.end()));
        fill(tans.begin(),tans.end(),0);
    }
    return mx;
}
