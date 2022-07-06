#include "rainbow.h"
#include <algorithm>
#include <vector>
#include <tuple>
#define x first
#define y second
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define sort_and_unique(v) { sort(all(v)); v.erase(unique(all(v)), v.end()); }
using namespace std;
using pp=pair<int,int>;
using ll=long long;

const int maxm = int(1e5) + 10;

vector<pp> riv, eh, ev, e4;
void River(int sx, int sy, int m, char *s) {
	riv.resize(m+1);
	for (int i=0; i<m; ++i) {
		riv[i] = {sx, sy};
		if (s[i] == 'S') ++sx; else if (s[i] == 'N') --sx;
		else if (s[i] == 'E') ++sy; else --sy;
	}
	riv[m++] = {sx, sy};
	sort_and_unique(riv); m = riv.size();
	eh = riv; ev = riv; eh.resize(2*m); ev.resize(2*m);
	for (int i=0, x, y; i<m; ++i) { tie(x, y) = riv[i];
		eh[m+i] = {x, y-1}; ev[m+i] = {x-1, y};
	}
	sort_and_unique(eh); sort_and_unique(ev);
	e4 = riv; e4.resize(4*m);
	for (int i=0, j=m, x, y; i<m; ++i) { tie(x, y) = riv[i];
		e4[j++] = {x-1, y};
		e4[j++] = {x, y-1};
		e4[j++] = {x-1, y-1};
	}
	sort_and_unique(e4);
}

struct MST {
	const static int M = 262144;
	vector<int> t[M<<1];
	void put(int x, int y) { t[M+x].pb(y); }
	void init() {
		for (int i=0; i<M; ++i) sort(all(t[M+i]));
		for (int i=M-1; 1<=i; --i) {
			static int tmp[4*maxm];
			t[i] = vector<int>(tmp, merge(all(t[i*2]), all(t[i*2+1]), tmp));
		}
	}
	int rq(int l, int r, int d, int u) { if (d>u) return 0;
		int x = 0;
		auto vq = [&](const vector<int> &v) -> int {
			return upper_bound(all(v), u) - lower_bound(all(v), d);
		};
		for (l+=M, r+=M; l<=r; l/=2, r/=2) {
			if (l%2 == 1) x += vq(t[l++]);
			if (r%2 == 0) x += vq(t[r--]);
		}
		return x;
	}
} triv, teh, tev, te4;

void Write() {
#define wr(v, t) for (auto &tmp:v) t.put(tmp.x, tmp.y); t.init();
	wr(riv, triv);
	wr(eh, teh);
	wr(ev, tev);
	wr(e4, te4);
#undef wr
}

pp rmn, rmx;
void init(int R, int C, int sr, int sc, int M, char *S) {
	River(sr, sc, M, S);
	Write();
	rmn = {1e9, 1e9};
	rmx = {-1e9, -1e9};
	for (auto &tmp:riv) {
		rmn.x = min(rmn.x, tmp.x);
		rmn.y = min(rmn.y, tmp.y);
		rmx.x = max(rmx.x, tmp.x);
		rmx.y = max(rmx.y, tmp.y);
	}
}

int colour(int ar, int ac, int br, int bc) {
	ll w = br-ar+1, h = bc-ac+1;
	ll inv = w * h;
	ll ine = (w-1)*h + w*(h-1);
	ll inf = (w-1)*(h-1);

	inv -= triv.rq(ar, br, ac, bc);
	ine -= teh.rq(ar, br, ac, bc-1);
	ine -= tev.rq(ar, br-1, ac, bc);
	inf -= te4.rq(ar, br-1, ac, bc-1);

	if (ar < rmn.x && rmx.x < br &&
		ac < rmn.y && rmx.y < bc) ++inf;

    return inv - ine + inf;
}

