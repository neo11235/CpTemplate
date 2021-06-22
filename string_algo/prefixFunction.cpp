void pi_function(char* str,int sz,int* pi){//prefix function
    pi[0]=0;
    int i,j;
    for(i=1;i<sz;i++){
        j=pi[i-1];
        while(j>0&&str[i]!=str[j])j=pi[j-1];
        if(str[i]==str[j])j++;
        pi[i]=j;
    }
    return;
}
void pi_function(string const &str,vector<int> & pi)
{
    int sz=str.length();
    assert(sz<=(int)pi.size());
    pi[0]=0;
    int i,j;
    for(i=1;i<sz;i++){
        j=pi[i-1];
        while(j>0&&str[i]!=str[j])j=pi[j-1];
        if(str[i]==str[j])j++;
        pi[i]=j;
    }
    return;
}
//computes number of occurrences of each prefix
void noc(vector<int>& pi,vector<int>& res,int n)
{
    assert((int)res.size()>n&&(int)pi.size()>=n);
    fill(res.begin(),res.begin()+n+1,0);
    for(int i=0;i<n;i++)
    {
        ++res[pi[i]];
    }
    for(int i=n-1;i>0;i--)
    {
        res[pi[i-1]]+=res[i];
    }
    for(int i=0;i<=n;i++)
        ++res[i];
}
//pass s+'#' and its computed prefix function
//length of aut should be n
void computeAutomation(const string &s,vector<int>& pi,int aut[][26])
{
    assert(aut);
    int n=(int)s.size();
    for(int i=0;i<n;i++)
    {
        for(int c=0;c<26;c++)
        {
            if(i>0&&s[i]!='a'+c)
                aut[i][c]=aut[pi[i-1]][c];
            else
                aut[i][c]=i+('a'+c==s[i]);
        }
    }
}
//computes pi(s1+'#'+s2)
//tested only once
void pi_function(string const& s1,string const& s2,vector<int> &pi)
{
    int l1=(int)s1.length();
    int l2=(int)s2.length();
    pi_function(s1,pi);
    pi[l1]=0;
    int l=(l1+l2+1);
    for(int i=l1+1;i<l;i++)
    {
        int j=pi[i-1];
        while(j>0&&s2[i-l1-1]!=s1[j])
            j=pi[j-1];
        if(s2[i-l1-1]==s1[j])j++;
        pi[i]=j;
    }
}
