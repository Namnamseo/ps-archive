#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;

const int maxn = int(1e6) + 10;
const ll inf = ll(4e15);

int n; ll L;
ll P[maxn], D[maxn], A[maxn], B[maxn];

int sortedAIdx[maxn];
int sortedBIdx[maxn];

struct MaxSystem {
	ll m, sm; int mi, smi;
	MaxSystem() { mi = smi = -1; }
	void eat(ll x, int i) {
		if (mi == -1) {
			m = x; mi = i;
		} else if (m <= x) {
			sm = m; smi = mi;
			m = x; mi = i;
		} else if (smi == -1 || sm < x) {
			sm = x; smi = i;
		}
	}

	ll max_ineq(int i) {
		if (mi == -1) return -inf;
		else if (mi != i) return m;
		else if (smi == -1) return -inf;
		else return sm;
	}
};

bool can_satisfy(ll V) {
	ll plus_min = -inf, plus_max = inf;
	ll minus_min = -inf, minus_max = inf;

	MaxSystem maxAiS, maxBiS;
	int maxBIdx = n;
	for (int jth=0; jth<n; ++jth) {
		int j = sortedAIdx[jth];

		ll allowedMinBi = V-A[j]+1;
		while (0 < maxBIdx && allowedMinBi <= B[sortedBIdx[maxBIdx-1]]) {
			--maxBIdx;
			int i = sortedBIdx[maxBIdx];
			maxAiS.eat(A[i], i);
			maxBiS.eat(B[i], i);
		}

		ll maxAi = maxAiS.max_ineq(j);
		ll maxBi = maxBiS.max_ineq(j);

		plus_min = max(plus_min, maxAi + A[j] - V + L);
		plus_max = min(plus_max, V - L - maxBi - B[j]);
		minus_min = max(minus_min, maxAi + B[j] - V + L);
		minus_max = min(minus_max, V - L - maxBi - A[j]);
	}

	int i1L = n, i1R = n-1;
	int i2L = 0, i2R = -1;
	for (int y=0; y<n; ++y) {
		ll gug1L = plus_min - P[y], gug1R = plus_max - P[y];
		ll gug2L = minus_min + P[y], gug2R = minus_max + P[y];

		while (0 < i1L && gug1L <= P[i1L-1]) --i1L;
		while (0 <= i1R && gug1R < P[i1R]) --i1R;
		while (i2L < n && P[i2L] < gug2L) ++i2L;
		while (i2R+1 < n && P[i2R+1] <= gug2R) ++i2R;

		if (max(i1L, i2L) <= min(i1R, i2R)) return true;
	}

	return false;
}

void prepare() {
	iota(sortedAIdx, sortedAIdx+n, 0);
	sort(sortedAIdx, sortedAIdx+n, [](const int& i, const int& j) { return A[i] < A[j]; });
	iota(sortedBIdx, sortedBIdx+n, 0);
	sort(sortedBIdx, sortedBIdx+n, [](const int& i, const int& j) { return B[i] < B[j]; });
}

ll find_shortcut(int n_, vector<int> l, vector<int> d, int c) {
	n = n_; L = c;
	copy(d.begin(), d.end(), D);
	for (int i=1; i<n; ++i) P[i] = P[i-1] + l[i-1];
	for (int i=0; i<n; ++i) A[i] = D[i] + P[i], B[i] = D[i] - P[i];

	prepare();

	MaxSystem dmax;
	for (int i=0; i<n; ++i) dmax.eat(D[i], i);

	ll left = dmax.m + dmax.sm, right = ll(1e15) + ll(2e9) + 10;
	while (left + 1 < right) {
		ll md = (left + right) / 2;
		(can_satisfy(md) ? right : left) = md;
	}

	return right;
}

