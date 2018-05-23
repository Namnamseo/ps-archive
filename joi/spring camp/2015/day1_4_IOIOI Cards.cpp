#include <bits/stdc++.h>
using namespace std;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
typedef long long ll;
#define pb push_back

vector<int> pt;
int n;

typedef pair<int,int> pp;
typedef pair<ll,int> pli;
vector<pp> edge[500010];

ll dist[500010];
ll inf=1ll<<60;

priority_queue<pli> pq;

void dijk(int x){
    for(int i=0; i<=n; ++i) dist[i]=inf;
    dist[x]=0;
    pq.push({0LL, x});
    while(pq.size()){
        ll dst;
        int p;
        tie(dst, p) = pq.top(); pq.pop();
        if(dst != -dist[p]) continue;
        for(auto tmp:edge[p]){
            int y, d; tie(y, d) = tmp;
            if(dist[y] > dist[p]+d){
                dist[y] = dist[p]+d;
                pq.push({-dist[y], y});
            }
        }
    }
}

ll dpt[4][4];

int main()
{
    for(int i=0; i<5; ++i){
        int x; read(x);
        if(n){
            pt.pb(n);
        }
        n += x;
    }

    int q;
    read(q);
    for(;q--;){
        int l, r; read(l, r);
        --l;
        edge[l].pb({r, r-l});
        edge[r].pb({l, r-l});
    }
    
    for(int i=0; i<4; ++i){
        dijk(pt[i]);
        for(int j=i+1; j<4; ++j){
            dpt[i][j] = dpt[j][i] = dist[pt[j]];
        }
    }
    
    ll ans = min({
        dpt[0][1] + dpt[2][3],
        dpt[0][2] + dpt[1][3],
        dpt[0][3] + dpt[2][1]
    });
    
    if(ans > inf) puts("-1");
    else printf("%lld\n", ans);
    return 0;
}
