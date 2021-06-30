///old implementation
void z_function(char* str,int sz,int* z){
    z[0]=1;
    int i,l=0,r=0,j,k;
    for(i=1;i<sz;i++){
        z[i]=0;
        if(i<=r){
            z[i]=min(r-i+1,z[i-l]);
        }
        while(i+z[i]<sz&&str[z[i]]==str[i+z[i]])z[i]++;
        if(i+z[i]-1>r){
            l=i;
            r=i+z[i]-1;
        }
    }
    return;
}
/*********************************************/
void z_function(const string& str,vector<int>& z){
    int sz=str.size();
    z[0]=0;//really dont know why i assigned z[0]=1 in previous implementation
    int i,l=0,r=0,j,k;
    for(i=1;i<sz;i++){
        z[i]=0;
        if(i<=r){
            z[i]=min(r-i+1,z[i-l]);
        }
        while(i+z[i]<sz&&str[z[i]]==str[i+z[i]])z[i]++;
        if(i+z[i]-1>r){
            l=i;
            r=i+z[i]-1;
        }
    }
    return;
}
