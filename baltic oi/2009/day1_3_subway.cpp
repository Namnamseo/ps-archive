#include <bits/stdc++.h>
using namespace std;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back

typedef long long ll;

int n, m;

int x[100010];

vector<ll> getX(ll s){
    ll df = m*4LL;
    int dir=1;
    vector<ll> ret[2];
    for(int i=0; i<n; ++i){
        ret[(1-dir)/2].pb(s);
        s += df*dir;
        if(s >= m*2ll*n){
            s = m*4ll*n - s;
            dir = -dir;
        }
    }
    reverse(all(ret[1]));
    vector<ll> ans;
    int i=0, j=0;
    while(true){
        if(i < ret[0].size()){
            ans.pb(ret[0][i++]);
            if(j < ret[1].size()) ans.pb(ret[1][j++]);
        } else break;
    }
    return ans;
}

ll diff(ll x){
    auto tmp = getX(x);
    ll ret=0;
    for(int i=1; i<=n; ++i) ret=max(ret, abs(tmp[i-1]-::x[i]*2LL*n));
    return ret;
}

int main()
{
    read(m, n);
    for(int i=1; i<=n; ++i) read(x[i]), scanf("%*s");
    sort(x+1, x+n+1);
    int l=0, r=2*m;
    while(l+3 < r){
        int p1=(l*2+r)/3;
        int p2=(l+2*r)/3;
        ll v1=diff(p1);
        ll v2=diff(p2);
        if(v1 > v2) l=p1; else r=p2;
    }
    ll ans=(1ull << 62);
    for(int i=l; i<=r; ++i) ans=min(ans, diff(i));
    printf("%.6f\n", ans*0.5/n);
    return 0;
}
