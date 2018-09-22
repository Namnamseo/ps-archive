#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
void read(pp& x){ scanf("%d%d",&x.first, &x.second); }
void read(pll& x){ scanf("%lld%lld",&x.first, &x.second); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define sz(x) (int)(x).size()

int n_lo, n_hi;

ll dp[6][200010];
vector<ll> h[6];

ll ab;

const int M = 200000;

const ll inf = (1ll<<60);

void work(ll x, ll mod, ll cl, ll cr, ll ul, ll ur){
	if(cl > cr || ul > ur) return;
	ll mid = (cl+cr)/2;
	int mp = -1;
	ll& cv = dp[x][x*mid+mod];
	for(int i=ul; i<=ur && i<=mid; ++i){
		if(mid-i >= int(h[x].size())) continue;
		ll nv = dp[x-1][x*i+mod] + h[x][mid-i];
		if(cv <= nv){
			cv = nv;
			mp = i;
		}
	}
	work(x, mod, cl, mid-1, ul, mp);
	work(x, mod, mid+1, cr, mp, ur);
}

int main()
{
	read(n_lo, n_hi);
	int m; read(m);
	for(;m--;){
		int g, s; read(g, s);
		if(g) h[g].pb(s);
		else if(s>0) ab += s;
	}

	fill(dp[0]+1, dp[0]+M+1, -inf);
	rrep(x, 5){
		sort(all(h[x]), greater<ll>());
		h[x].insert(h[x].begin(), 0ll);
		partial_sum(all(h[x]), h[x].begin());

		fill(dp[x], dp[x]+M+1, -inf);
		rep(mod, x){
			int max_c = (M - mod) / x;
			work(x, mod, 0, max_c, 0, max_c);
		}
	}

	printf("%lld\n", *max_element(dp[5]+n_lo, dp[5]+n_hi+1) + ab);

	return 0;
}
