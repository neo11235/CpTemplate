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
