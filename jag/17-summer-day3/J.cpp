#include <algorithm>
#include <numeric>
#include <cstring>
#include <iostream>
using namespace std;
using ll=long long;

const int maxn = 40 + 10, maxk = int(2e5) + 10;

int n, m, k, q;
int open[maxn], close_sum;

static const int M = 262144;
struct T {
	ll t[M<<1];
	void init(ll *ways) {
		memset(t, -1, sizeof(t));
		copy(ways, ways+k+1, t+M);
		for (int i=M-1; 1<=i; --i) t[i] = t[i*2] & t[i*2+1];
	}
	ll range(int l, int r) {
		ll ret = -1;
		for (l+=M, r+=M; l<=r; l/=2, r/=2) {
			if (l%2 == 1) ret &= t[l++];
			if (r%2 == 0) ret &= t[r--];
		}
		return ret;
	}
} filler;

void Build() {
	static ll ways[maxk];
	int open_sum = k - close_sum;

	memset(ways, 0xff, sizeof(ll)*(open_sum+1));
	ways[0] = 0;
	for (int i=0; i<n; ++i) {
		int x = open[i];
		for (int j=open_sum; j>=x; --j) {
			ways[j] &= (ways[j-x] | (1ll<<i));
		}
	}

	filler.init(ways);
}

int main() { cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m >> k >> q;
	for (int i=0; i<n; ++i) cin >> open[i];
	close_sum = k - accumulate(open, open+n, 0);
	Build();

	int open_min = *min_element(open, open+n);

for(;q--;) {
	int X; cin >> X;
	ll ans = -1;
	for (ll ccl=0; ccl<=m; ++ccl) {
		ll cmin = max(ccl, close_sum - (m-ccl) * (open_min-1));
		ll cmax = min(ccl * (open_min-1), close_sum - (m-ccl));
		if (cmin > cmax) continue;
		ll omin = X-cmax, omax = X-cmin;
		omin = max(0ll, omin);
		omax = min(omax, ll(k-close_sum));
		if (omin > omax) continue;
		ll tmp = filler.range(omin, omax);
		ans &= tmp;
	}
	static int al[maxn]; int aln = 0;
	for (int i=0; i<n; ++i) if (1&(ans>>i)) al[aln++] = i+1;
	if (!aln) { cout << "-1\n"; continue; }
	for (int i=0; i<aln; ++i) cout << al[i] << " \n"[i+1 == aln];
}

	return 0;
}
