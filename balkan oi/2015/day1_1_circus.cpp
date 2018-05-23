#include <bits/stdc++.h>
#include "circus.h"
using namespace std;

typedef tuple<int,int,int> tp;

priority_queue<tp> pq;
int dist[100010][2];
int alld[100010];
const int inf = (1LL<<30);

int n;

int p[100010];

int Lp[100010];
int Lv[100010];
int Ln;

int Rp[100010];
int Rv[100010];
int Rn;

void precalc(){
    for(int i=0; i<n; ++i){
        int x=p[i]+alld[i];
        Lp[i] = x;
    }
    sort(Lp, Lp+n);
    Ln = unique(Lp, Lp+n) - Lp;
    for(int i=0; i<Ln; ++i) Lv[i] = inf;
    for(int i=0; i<n; ++i){
        int x=lower_bound(Lp, Lp+Ln, p[i]+alld[i]) - Lp, y=-p[i];
        Lv[x] = min(Lv[x], y);
    }
    for(int i=1; i<Ln; ++i) Lv[i] = min(Lv[i], Lv[i-1]);

    for(int i=0; i<n; ++i){
        int x=p[i]-alld[i];
        Rp[i] = x;
    }
    sort(Rp, Rp+n);
    Rn = unique(Rp, Rp+n) - Rp;
    for(int i=0; i<Rn; ++i) Rv[i] = inf;
    for(int i=0; i<n; ++i){
        int x=lower_bound(Rp, Rp+Rn, p[i]-alld[i]) - Rp, y=p[i];
        Rv[x] = min(Rv[x], y);
    }
    for(int i=Rn-2; 0<=i; --i) Rv[i] = min(Rv[i], Rv[i+1]);
}

void init(int n, int m, int p_given[]){
    ::n = n+1;
    for(int i=0; i<n; ++i) p[i]=p_given[i];
    sort(p, p+n);
    for(int i=0; i<n; ++i){
        dist[i][0] = inf;
        dist[i][1] = inf;
    }
    p[n++] = m;

    dist[n-1][0]=inf;
    dist[n-2][1]=p[n-1]-p[n-2];
    pq.push(make_tuple(-dist[n-2][1], n-2, n-1));
    while(pq.size()){
        int dst, x, from;
        tie(dst, x, from) = pq.top(); pq.pop();
        dst = -dst;
        if(dist[x][x<from] != dst) continue;

        int lp = upper_bound(p, p+n, p[x]-dst)-p-1;
        if(0<=lp && lp < x){
            if(dist[lp][1] > (p[x]-p[lp])){
                dist[lp][1] = p[x]-p[lp];
                pq.emplace(-dist[lp][1], lp, x);
            }
        }

        int rp = lower_bound(p, p+n, p[x]+dst)-p;
        if(x < rp && rp < n){
            if(dist[rp][0] > (p[rp]-p[x])){
                dist[rp][0] = p[rp]-p[x];
                pq.emplace(-dist[rp][0], rp, x);
            }
        }

        int sgn=0, len;
        if(x < from && 0 <= x-1){
            sgn = -1; len = p[from]-p[x-1];
        } else if(from < x && x+1 < n){
            sgn = 1; len = p[x+1] - p[from];
        }
        if(sgn){
            if(dist[x+sgn][x<from] > len){
                dist[x+sgn][x<from] = len;
                pq.emplace(-dist[x+sgn][x<from], x+sgn, from);
            }
        }
    }

    for(int i=0; i<n; ++i) alld[i]=min(dist[i][0], dist[i][1]);

    precalc();
}

int minLength(int D){
    int ans=inf;

    int lp = upper_bound(Lp, Lp+Ln, D) - Lp;
    if(lp != 0)
        ans = min(ans, D+Lv[lp-1]);

    int rp = lower_bound(Rp, Rp+Rn, D) - Rp;
    if(rp != Rn)
        ans = min(ans, Rv[rp]-D);

    return ans;
}
