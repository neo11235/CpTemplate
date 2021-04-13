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
