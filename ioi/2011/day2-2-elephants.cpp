#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cstring>
#define BS 400
using namespace std;

int n;
int l;

struct buck {
    int pos[1010];
    int dp [1010];
    int ep [1010];
    int sz;
    buck(){ sz=0; }

    void recalcDP(int until){
        for(int i=until; 0<=i; --i){
            auto it=upper_bound(pos, pos+sz, pos[i]+l);

            if(it == pos+sz){
                dp[i] = 0;
                ep[i] = pos[i];
            } else {
                dp[i] = 1+dp[it-pos];
                ep[i] = ep[it-pos];
            }
        }
    }

    void ins(int x){
        if(sz == 0){
            pos[0] = x;
            dp [0] = 0;
            ep [0] = x;
            sz = 1;
            return;
        }
        auto it=upper_bound(pos, pos+sz, x);
        if(it != pos+sz){
            rotate(it, pos+sz, pos+sz+1);
            rotate(dp+(it-pos), dp+sz, dp+sz+1);
            rotate(ep+(it-pos), ep+sz, ep+sz+1);
        }
        *it = x;
        ++sz;

        recalcDP(it-pos);
    }

    void rem(int x){
        int p = lower_bound(pos, pos+sz, x)-pos;
        rotate(pos+p, pos+p+1, pos+sz);
        rotate(dp +p, dp +p+1, dp +sz);
        rotate(ep +p, ep +p+1, ep +sz);
        --sz;

        if(sz) recalcDP(min(sz-1,p));
    }
} bucks[510];
int bn;

int findBuck(int x){
    if(x < bucks[0].pos[0]) return 0;
    for(int i=0; i<bn; ++i){
        if(bucks[i].pos[0]<=x && (i==bn-1 || x<bucks[i+1].pos[0])) return i;
    }
    for(;;);
    return -1;
}

int sqrtN;

int pos   [150001];
int sorted[150001];

void recreateBuck(bool init){
    if(init){
        memcpy(sorted, pos, n*sizeof(int));
    } else {
        int ind = 0;
        for(int i=0; i<bn; ++i){
            int *arr = bucks[i].pos;
            int sz=bucks[i].sz;
            for(int j=0; j<sz; ++j){
                sorted[ind++] = arr[j];
            }
            bucks[i].sz = 0;
        }
    }

    bn = 0;
    for(int i=0; i<n; ++i){
        int cb=i/BS;
        if(cb >= bn) ++bn;
        int& sz=bucks[cb].sz;
        bucks[cb].pos[sz++] = sorted[i];
    }
    for(int i=0; i<bn; ++i){
        bucks[i].recalcDP(bucks[i].sz-1);
    }
}

void init(int N, int L, int X[])
{
    n = N; l = L;

    for(int i=0; i<n; ++i) pos[i] = X[i];

    recreateBuck(1);
}

int timer = 0;

int getAns(){
    int lastP = bucks[0].ep[0];
    int ans = bucks[0].dp[0];

    for(int i=1; i<bn; ++i){
        if(lastP + l >= bucks[i].pos[bucks[i].sz-1]) continue;
        ++ans;
        int ind = upper_bound(bucks[i].pos, bucks[i].pos+bucks[i].sz, lastP+l)-bucks[i].pos;
        ans += bucks[i].dp[ind];
        lastP = bucks[i].ep[ind];
    }
    ++ans;
    return ans;
}

int update(int i, int y)
{
    int t = findBuck(pos[i]);
    int nt = findBuck(y);
    bucks[t].rem(pos[i]);

    pos[i]=y;

    bucks[nt].ins(y);

    ++timer;
    if(timer >= BS){
        recreateBuck(0);
        timer = 0;
    }
    return getAns();
}
