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
void cppio(){ ios_base::sync_with_stdio(0); cin.tie(0); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define sz(x) (int)(x).size()

int n;

bitset<3010> a, b;

ll fact[3010];
ll finv[3010];
ll comb[3010][3010];
ll A[3010];

const ll mod = int(1e9) + 7;

ll minv(ll x) {
	ll ret = 1, e = mod-2;
	while(e) {
		if (e&1) (ret*=x)%=mod;
		(x*=x)%=mod; e/=2;
	}
	return ret;
}

void F() {
	fact[0] = 1;
	rrep(i, n) fact[i] = fact[i-1] * i % mod;
	finv[n] = minv(fact[n]);
	for(int i=n; 1<=i; --i) finv[i-1] = finv[i] * i % mod;
	comb[0][0] = 1;
	for(int i=1; i<=n; ++i) {
		comb[i][0] = comb[i][i] = 1;
		for(int j=1; j<i; ++j) {
			comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % mod;
		}
	}
}

vector<int> G() {
	vector<int> il;
	for(int i=0; i<=n; ++i) if (a[i]&&b[i]) il.pb(i);
	vector<int> gs;
	for(int i=0; i+1<sz(il); ++i)
		if (il[i+1] > il[i]+1 && (il[i+1] > il[i]+2 || (a[il[i]+1] || b[il[i]+1])))
			gs.pb(il[i+1]-il[i]);
	return gs;
}

int main()
{
	cppio(); cin >> n;
	{auto f=[](bitset<3010>& b) {
		int k, s=0, x; cin >> k;
		b[0] = 1;
		for(;k--;) {
			cin >> x;
			b[s+=x] = 1;
		}
	};
	f(a); f(b);}

	F();
	auto gs = G();
	int cost = 0;
	for(int x:gs) cost += x-1;

	cout << cost << ' ';

	A[0] = A[1] = 1;
	for(int i=1; i<=n; ++i) {
		for(int j=0; j<=i; ++j)
			(A[i+1] += comb[i][j] * A[j] % mod * A[i-j] % mod) %= mod;
		(A[i+1] *= (mod+1)/2) %= mod;
	}

	ll ways = fact[cost];
	for (int x:gs) {
		ways = (ways * A[x-1] % mod * finv[x-1] % mod);
	}

	cout << ways << endl;

	return 0;
}
