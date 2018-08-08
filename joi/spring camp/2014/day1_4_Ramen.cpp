#include "ramen.h"

int a[1024];
int b[1024];

void Ramen (int n){
    int i, ind=0;
    for(i=0;i*2+1<n;++i){
        if(Compare(i*2,i*2+1)==1){
            a[ind]=i*2; b[ind]=i*2+1;
        } else {
            a[ind]=i*2+1; b[ind]=i*2;
        }
        ++ind;
    }
    if(n&1) a[ind]=b[ind]=n-1, ++ind;
    int M=a[0], m=b[0];
    for(i=1;i<ind;++i){
        if(Compare(M,a[i])==-1) M=a[i];
        if(Compare(b[i],m)==-1) m=b[i];
    }
    Answer(m,M);
}
