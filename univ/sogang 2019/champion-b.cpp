#include <iostream>
using namespace std;
using ll=long long;

int n, m, b;
int hc[257];

int main() { cin.tie(0)->sync_with_stdio(0);

	cin >> n >> m >> b;
	for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) { int x; cin >> x; ++hc[x]; }

	ll mintime = 1ll<<60;
	int anshei = -1;

	for (int to=0; to<=256; ++to) {
		long long removes = 0, adds = 0;
		for (int i=0; i<to; ++i) {
			adds += (to-i) * 1ll * hc[i];
		}
		for (int i=to+1; i<=256; ++i) {
			removes += (i-to) * 1ll * hc[i];
		}
		if (adds - removes > b) continue;
		ll tm = removes * 2 + adds;
		if (mintime >= tm) {
			mintime = tm;
			anshei = to;
		}
	}

	cout << mintime << ' ' << anshei << '\n';

	return 0;
}
