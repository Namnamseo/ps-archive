#include "cave.h"
#include <cstdio>

int  trial_array   [5010];

bool fixed_point   [5010];

int switch_forward [5010];
int switch_reverse [5010];
int switch_parity  [5010];

int n;

int try_wrapper(){
    int tmp = tryCombination(trial_array);
    if(tmp<0) tmp=2*n;
    return tmp;
}

void find_switch(int l,int r,int target,int zero_result){
    if(l==r){
        switch_reverse[target]=l;
        switch_forward[l]=target;
        switch_parity [l]=1-zero_result;
        fixed_point   [l]=1;
    } else {
        int m=(l+r)/2;
        int i;
        for(i=l; i<=m; ++i) if(!fixed_point[i]) trial_array[i]=1;
        int result = try_wrapper();
        for(i=l; i<=m; ++i) if(!fixed_point[i]) trial_array[i]=0;
        if((result != target) == !zero_result) {
            find_switch(l  , m, target, zero_result);
        } else {
            find_switch(m+1, r, target, zero_result);
        }
    }
}

void exploreCave(int n) {
    ::n=n;
    int i,j;
    for(i=0;i<n;++i){
        for(j=0;j<n;++j) trial_array[j]=0;
        for(j=0; j<i; ++j) {
            trial_array[switch_reverse[j]]=switch_parity[switch_reverse[j]];
        }
        find_switch(0,n-1, i,(try_wrapper() != i));
    }
    answer(switch_parity, switch_forward);
}
