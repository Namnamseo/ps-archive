#include "sorting.h"
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int,int> pp;

int *x;
int n;

int *ea, *eb;
int *oa, *ob;

int cur[200010];
int mp [200010];

void w(int a,int b){
    swap(cur[a], cur[b]);
    swap(mp[cur[a]], mp[cur[b]]);
}

bool possible(int t){
    for(int i=0; i<n; ++i) cur[i] = x[i], mp[x[i]]=i;
    for(int i=0; i<t; ++i){
        int a=ea[i], b=eb[i];
        w(a,b);
    }
    int ind=0;
    for(int i=0; i<n; ++i){
        if(mp[i]==i) continue;
        int a=i, b=mp[i];
        oa[ind]=cur[i]; ob[ind]=i; ++ind;
        w(a, b);
    }
    if(ind>t) return false;
    for(;ind<t;++ind) oa[ind]=ob[ind]=0;
    for(int i=0; i<n; ++i) cur[i] = x[i], mp[x[i]]=i;
    for(int i=0; i<t; ++i){
        int a=ea[i], b=eb[i];
        swap(cur[a], cur[b]); swap(mp[cur[a]], mp[cur[b]]);
        
        int p=oa[i], q=ob[i];
        oa[i]=mp[p]; ob[i]=mp[q];
        w(oa[i], ob[i]);
    }
    return true;
}

int findSwapPairs(int N, int x_[], int m, int EA[], int EB[], int p[], int q[]) {
    n=N;
    x=x_;
    ea=EA; eb=EB;
    oa=p;  ob=q;
    int l=0, r=m;
    if(possible(l)) return l;
    while(l+1<r){
        int mid=(l+r)/2;
        if(possible(mid)) r=mid;
        else l=mid;
    }
    possible(r);
    return r;
}
