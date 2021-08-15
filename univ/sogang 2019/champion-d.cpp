#include <iostream>
using namespace std;
const int maxn = int(1e6) + 10;

int q;
int par[maxn];
int sz[maxn];
int root(int x) { int r = x; while (par[r] != r) r=par[r]; while (x != r) { int t = par[x]; par[x] = r; x = t; } return r; }

struct Init {
	constexpr Init() {
		for (int i=1; i<=int(1e6); ++i) par[i] = i, sz[i] = 1;
	}
} _;

void Join(int a, int b) {
	a = root(a); b = root(b); if (a == b) return;
	if (a&1) { int t=a; a=b; b=t; }
	sz[b] += sz[a]; par[a] = b;
}

int main() { cin.tie(0)->sync_with_stdio(0);
	cin >> q;
	char cmd[3];
	for(;q--;) {
		cin >> cmd;
		if (cmd[0] == 'I') {
			int a, b; cin >> a >> b; Join(a, b);
		} else {
			int a; cin >> a; a = root(a);
			cout << sz[a] << '\n';
		}
	}
	return 0;
}
