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
#define eb emplace_back
#define x first
#define y second

int n, k;
const ll mod = 1'000'000'007;

ll fact[200001];

ll Pow(ll b, ll e){
    ll ret=1;
    while(e){
        if(e&1) (ret*=b)%=mod;
        e/=2; (b*=b)%=mod;
    }
    return ret;
}

ll Comb(ll n, ll r){
    if(r<0 || r>n) return 0;
    return fact[n]*Pow(fact[r], mod-2)%mod*Pow(fact[n-r], mod-2)%mod;
}

int main()
{
    fact[0]=1; for(int i=1; i<=200000; ++i) fact[i]=fact[i-1]*i%mod;

    int n, k;
    cin >> n >> k; --k;
    ll ans = 0;
    for(int j=0; j<=k; ++j){
        (ans += ((j%2?-1:1)*Comb(n+1, j)*Pow(k-j+1, n)%mod+mod)%mod) %= mod;
    }
    cout << ans;
    return 0;
}
