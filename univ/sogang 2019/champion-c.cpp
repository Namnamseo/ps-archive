#include <iostream>
using namespace std;
const int maxn = int(1e6) + 10;

int n;
int ans[maxn];
int cards[maxn], hd, tl;

int main() { cin.tie(0)->sync_with_stdio(0);
	cin >> n;
	for (int i=1; i<=n; ++i) cards[i] = i;
	hd = 1; tl = n;
	for (int i=1; i<=n; ++i) {
		int cmd; cin >> cmd;
		if (cmd == 1) {
			ans[cards[hd++]] = n+1-i;
		} else if (cmd == 2) {
			ans[cards[hd+1]] = n+1-i;
			cards[hd+1] = cards[hd];
			++hd;
		} else {
			ans[cards[tl--]] = n+1-i;
		}
	}

	for (int i=1; i<=n; ++i) cout << ans[i] << " \n"[i == n];
	return 0;
}
