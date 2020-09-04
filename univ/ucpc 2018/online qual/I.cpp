#include <iostream>
#define rep(i, n) for(int i=0; i<n; ++i)
#include <algorithm>
#include <cstring>
using namespace std;

int n;

struct ing {
	int e[4][4];
	char c[4][4];
	ing rot() {
		ing ret;
		rep(i, 4) rep(j, 4)
			ret.e[j][3-i] = e[i][j],
			ret.c[j][3-i] = c[i][j];
		return ret;
	}
} id[10];

istream& operator>>(istream& is, ing& x) {
	rep(i, 4) rep(j, 4) is>>x.e[i][j];
	char buf[5];
	rep(i, 4) rep(j, 4) is>>buf, x.c[i][j] = buf[0];
	return is;
}

int E[128];
struct state {
	int v[5][5];
	char c[5][5];
	state() { memset(v, 0, sizeof(v)); memset(c, 0, sizeof(c)); }
	int z() {
		int ret = 0;
		rep(i, 5) rep(j, 5) ret += E[c[i][j]] * v[i][j];
		return ret;
	}
};

state add(state s, ing g, int dx, int dy) {
	rep(i, 4) rep(j, 4) {
		int &x = (s.v[i+dx][j+dy] += g.e[i][j]);
		if (x<0) x=0; if (x>9) x=9;
		if (g.c[i][j] != 'W')
			s.c[i+dx][j+dy] = g.c[i][j];
	}
	return s;
}

int ans;
void dfs(int D, state s, int m) {
	if (D == 3) { ans = max(ans, s.z()); return; }
	rep(i, n) if (!(1&(m>>i))) {
		rep(a, 2) rep(b, 2) {
			ing t = id[i];
			rep(p, 4) {
				dfs(D+1, add(s, t, a, b), m|(1<<i));
				t = t.rot();
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	E['R'] = 7;
	E['B'] = 5;
	E['G'] = 3;
	E['Y'] = 2;

	cin >> n;
	rep(i, n) cin >> id[i];

	dfs(0, state(), 0);

	cout << ans << endl;

	return 0;
}

