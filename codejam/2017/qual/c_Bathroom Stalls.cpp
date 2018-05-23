#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define x first
#define y second

ll n, k;

void Work(){
    read(n, k);
    map<ll,ll> m;
    m[-n]=1;
    --k;
    while(k){
        auto tmp = *m.begin();
        ll v = min(k, tmp.y);
        k-=v; tmp.y-=v;
        ll a=-tmp.x-1;
        m[-a/2]+=v;
        m[a/2-a]+=v;
        if(!tmp.y){
            m.erase(tmp.x);
        }
    }
    ll a=-m.begin()->first-1;
    printf("%lld %lld\n", a-a/2, a/2);
}

#define TYPE "l"

int main()
{
    freopen("in_" TYPE, "r", stdin);
    freopen("out_" TYPE, "w", stdout);
	int tc; read(tc);
	for(int i=1; i<=tc; ++i){
        printf("Case #%d: ", i);
        Work();
	}
    return 0;
}
