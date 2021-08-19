#include "horses.h"

typedef long long ll;

#include <bits/stdc++.h>
using namespace std;

int n;
int x[500010];
int y[500010];

struct segtype {
    double t[1048576];
    double left[1048576];
    int mi[1048576];
    static const int M=524288;
    void init(){
        for(int i=0; i<2*M; ++i){
            t[i]=left[i]=-1e300;
        }
    }
    void upd(int pos,double val){
        pos+=M;
        t[pos]=val; left[pos]=val; mi[pos]=pos-M; pos>>=1;
        while(pos){
            t[pos]=t[pos*2]+t[pos*2+1];
            left[pos]=max(left[pos*2], t[pos*2]+left[pos*2+1]);
            if(left[pos*2]>t[pos*2]+left[pos*2+1]) mi[pos]=mi[pos*2];
            else mi[pos]=mi[pos*2+1];
            pos>>=1;
        }
    }
} sumt;

const int D=int(1e9)+7;

struct segint{
    static const int M=524288;
    int t[M*2];
    void init(){
        for(int i=0; i<2*M; ++i) t[i]=1;
    }
    void upd(int pos,int val){
        pos+=M; t[pos]=val; pos>>=1;
        while(pos){
            t[pos]=t[pos*2]*1LL*t[pos*2+1]%D;
            pos>>=1;
        }
    }
    int rangePi(int l,int r){
        l+=M; r+=M;
        int ret=1;
        while(l<=r){
            if(l&1) ret=(ret*1LL*t[l++])%D;
            if((r&1)==0) ret=(ret*1LL*t[r--])%D;
            l>>=1; r>>=1;
        }
        return ret;
    }
} seg_int;

int init(int N, int X[], int Y[]) {
    n=N;
    for(int i=0; i<n; ++i){
        x[i]=X[i]; y[i]=Y[i];
    }
    sumt.init(); seg_int.init();
    sumt.upd(0, log(x[0]) + log(y[0]));
    seg_int.upd(0, x[0]);
    for(int i=1; i<n; ++i){
        sumt.upd(i, log(x[i])+log(y[i])-log(y[i-1]));
        seg_int.upd(i, x[i]);
    }
    int max_ind = sumt.mi[1];
    int a=seg_int.rangePi(0, max_ind);
    int b=y[max_ind];
    return a*1LL*b%D;
}

void refresh(int i){
    if(i>=n || i<0) return;
    double t=log(x[i])+log(y[i]);
    if(i) t -= log(y[i-1]);
    sumt.upd(i, t);
    seg_int.upd(i, x[i]);
}

int updateX(int pos, int val) {
    int i=pos;
    x[i]=val;
    refresh(i);
    int max_ind = sumt.mi[1];
    int a=seg_int.rangePi(0, max_ind);
    int b=y[max_ind];
    return a*1LL*b%D;
}

int updateY(int pos, int val) {
    y[pos]=val;
    refresh(pos); refresh(pos+1);
    int max_ind = sumt.mi[1];
    int a=seg_int.rangePi(0, max_ind);
    int b=y[max_ind];
    return a*1LL*b%D;
}
