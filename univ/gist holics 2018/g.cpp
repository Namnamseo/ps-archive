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

int n;
int b[101];

ll gcd(ll n, ll r){ return r?gcd(r, n%r):n; }

struct frac {
	ll mo, ja;

	frac(ll m=1, ll j=0) : mo(m), ja(j){
		if(mo<0) mo=-mo, ja=-ja;
		ll g = gcd(abs(mo), abs(ja));
		if(g) mo/=g, ja/=g;
	}

	bool operator<(const frac& r) const {
		return ja*r.mo < r.ja*mo;
	}

	bool operator==(const frac& r) const {
		return ja*r.mo == r.ja*mo;
	}
};

frac bl(1, 0), br(1, int(1e9));

int main()
{
	read(n); rep(i, n) read(b[i]);
	rep(i, n) rep(j, i){
		bl = max(bl, frac(i-j, b[i]-b[j]-1));
		br = min(br, frac(i-j, b[i]-b[j]+1));
	}
	if(bl < br){
		puts("pass");
	} else {
		puts("fail");
	}
	return 0;
}
