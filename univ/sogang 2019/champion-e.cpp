#include <iostream>
using namespace std;
using ll = unsigned long long;

ll mod;

ll modmul(ll a, ll b) {
	ll r = 0;
	while (b) {
		if (b&1) { r += a; if (r >= mod) r -= mod; }
		a <<= 1; if (a >= mod) a -= mod; b >>= 1;
	}
	return r;
}

ll ipow(ll b, ll e) {
	ll ret = 1;
	while (e) {
		if (e&1) ret = modmul(ret, b);
		b = modmul(b, b);
		e >>= 1;
	}
	return ret;
}

char ans[11000]; int ai;

int main() { cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
for(;tc--;) {
	ll a, i, n; cin >> a >> mod >> i >> n;
	a %= mod;
	ll t = modmul(a, ipow(10, i-1));
	for (int j=0; j<n; ++j) {
		ll q = 0;
		t *= 10;
		q = t/mod; t %= mod;
		ans[ai++] = 48+q;
	}
	ans[ai++] = 10;
}
	cout << ans;
	return 0;
}
