#include "ricehub.h"

long long prefix[100010];

long long sum(int a,int b){
    if(a==0) return prefix[b];
    return prefix[b]-prefix[a-1];
}

bool canUse(int from,int to,long long B){
    int middle = (to+from)/2;
    if((to-from)%2){
        return sum(middle+1,to) - sum(from,middle) <= B;
    } else {
        return sum(middle+1,to) - sum(from, middle-1) <= B;
    }
}

bool checkWidth(int r,long long Batt,int w){
    int i;
    if(w<=1) return true;
    for(i=0;i+w-1<r;i++) {
        if(canUse(i,i+w-1,Batt)) return true;
    }
    return false;
}


int besthub(int R, int L, int X[], long long B)
{
    int i;
    prefix[0]=X[0];
    
    for(i=1;i<R;i++){
        prefix[i]=prefix[i-1]+  X   [i];
    }
    int left = 1, right = R+1;
    int mid;
    while(left+1 != right){
        mid = (left+right)>>1;
        if(checkWidth(R,B,mid)){
            left=mid;
        } else {
            right=mid;
        }
    }
    return left;
}
