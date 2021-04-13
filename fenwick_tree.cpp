#include <bits/stdc++.h>
using namespace std;


#define LSB(i) ((i)&(-i))
#define SIZE 1000000
int ft[SIZE+1];
/**********implementation 1*******/
void add(int i,int k){
    while(i<=SIZE){
        ft[i]+=k;
        i+=LSB(i);
    }
}
int sum(int i){
    int s=0;
    while(i>0){
        s+=ft[i];
        i-=LSB(i);
    }
    return s;
}
/**********end**************/
