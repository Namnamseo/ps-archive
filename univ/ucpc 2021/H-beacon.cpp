#include <iostream>
using namespace std;
const int mod = int(1e9) + 7;

int main() { cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	int as=1, la=0;
	for (int i=1, mx=0; i<=n; ++i) {
		int h; cin >> h;
		if (mx < h) {
			la = as;
			mx = h;
		}
		as += la;
		if (as >= mod) as -= mod;
	}
	cout << la << '\n';
	return 0;
}
