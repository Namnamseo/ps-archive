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
int c[30];

ll comb[30][30];

ll gcd(ll a, ll b){ return b?gcd(b, a%b):a; }
struct frac {
	ll ja, mo;
	void init() {
		ll g = gcd(abs(ja), abs(mo));
		if (g) { ja /= g; mo /= g; }
		else mo = 1;
		if (mo < 0) ja = -ja, mo = -mo;
	}
	frac(ll J=0, ll M=1) : ja(J), mo(M) { init(); }
	bool operator<(const frac& r) const {
		return ja*r.mo < r.ja*mo;
	}
	frac recip() const { return frac(mo, ja); }
	frac operator+(const frac& r) const {
		ll mog = gcd(mo, r.mo);
		return frac(ja*(r.mo/mog)+r.ja*(mo/mog), mo/mog*r.mo);
	}
	frac operator-(const frac& r) const {
		ll mog = gcd(mo, r.mo);
		return frac(ja*(r.mo/mog)-r.ja*(mo/mog), mo/mog*r.mo);
	}
	frac operator*(const frac& r) const {
		ll j1 = ja, j2 = r.ja;
		ll m1 = mo, m2 = r.mo;
		ll g;
		g = gcd(abs(j2), m1); if (g > 1) j2 /= g, m1 /= g;
		g = gcd(abs(j1), m2); if (g > 1) j1 /= g, m2 /= g;
		return frac(j1*j2, m1*m2);
	}
	frac operator/(const frac& r) const {
		return (*this) * (r.recip());
	}
	frac operator-() const { return frac(-ja, mo); }
	frac operator*() const { return frac(-ja, mo); }
};

frac mat[30][30];
frac y[30];

ll work()
{
	for(int j=0; j<=n; ++j) {
		ll tmp = 0;
		for(int i=j; i<=n; ++i)
			tmp += c[i] * comb[i][j];
		y[j] = frac(tmp);
	}

	for(int i=0; i<=n; ++i)
		for(int j=i; j<=n; ++j)
			mat[i][j] = frac(comb[j+1][i]);

	ll ans = abs(c[0]);
	for(int i=n; 0<=i; --i) {
		y[i] = y[i] / mat[i][i];
		ans += abs(y[i].ja);
		for(int j=0; j<i; ++j)
			y[j] = y[j] - mat[j][i] * y[i];
	}

	return ans;
}

void build_comb()
{
	comb[0][0] = 1;
	rrep(i, 28) {
		comb[i][0] = comb[i][i] = 1;
		for(int j=1; j<i; ++j) comb[i][j] = (comb[i-1][j-1]+comb[i-1][j]);
	}
}

int main()
{
	cppio();
	build_comb();

int tc; cin >> tc;
for(;tc--;)
{
	cin >> n;
	for(int i=0; i<=n; ++i) cin >> c[i];
	cout << work() << '\n';
}

	return 0;
}
