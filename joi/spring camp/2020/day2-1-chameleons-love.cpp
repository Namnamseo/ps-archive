#include "chameleon.h"
#include <utility>
#include <vector>
using namespace std;
using vi=vector<int>;
using pp=pair<int,int>;
using pvi=pair<vi,vi>;
#define all(a) a.begin(), a.end()
#define pb push_back
#define sz(t) ((int)((t).size()))
const int maxn2 = int(1e3) + 10;

int n;

vector<pvi> v;
vi graph[maxn2];

bool Search(int i, vi &v, int l, int r, bool must=false) {
	if (l == r) return false;
	if (!must) {
		vi qry(v.begin()+l, v.begin()+r);
		qry.push_back(i);
		int qres = Query(qry);
		if (qres == sz(qry)) return false;
	}
	if (l+1 == r) {
		int j = v[l];
		graph[i].pb(j); graph[j].pb(i);
		return true;
	}
	int md = (l+r)/2;
	Search(i, v, md, r, !Search(i, v, l, md));
	return true;
}

void Rebuild(int p) {
	static bool vis[maxn2], col[maxn2];
	fill(vis+1, vis+p+1, 0);
	fill(col+1, col+p+1, 0);
	int vs = 0;
	for (int i=1; i<=p; ++i) if (!vis[i]) {
		static int q[maxn2], hd, tl;
		hd = 0; tl = 1; q[0] = i; vis[i] = true;
		if (sz(v) <= vs) v.resize(vs+1);
		v[vs].first.clear();
		v[vs].second.clear();
		while (hd < tl) {
			int x = q[hd++];
			(col[x]?v[vs].second:v[vs].first).push_back(x);
			for (int y:graph[x]) if (!vis[y]) {
				vis[y] = true;
				col[y] = !col[x];
				q[tl++] = y;
			}
		}
		++vs;
	}
	v.resize(vs);
}

void Solve(int N_) {
	n = N_;
	for (int i=1; i<=2*n; ++i) {
		static vi lefts, rights;
		lefts.clear(); rights.clear();
		for (auto &tmp : v) {
			if ((sz(tmp.first)<sz(tmp.second)) == (sz(lefts)<sz(rights)))
				swap(lefts, rights);
			lefts.insert(lefts.end(), all(tmp.first));
			rights.insert(rights.end(), all(tmp.second));
		}
		bool found = Search(i, lefts, 0, sz(lefts));
		found = Search(i, rights, 0, sz(rights)) || found;
		if (!found) v.push_back({{i}, {}});
		else Rebuild(i);
	}

	static bool is_directed[maxn2][maxn2];
	for (int i=1; i<=2*n; ++i) {
		if (sz(graph[i]) == 1) continue;
		int a = graph[i][0], b = graph[i][1], c = graph[i][2];
		if (is_directed[i][a] + is_directed[i][b] + is_directed[i][c] == 2) {
			continue;
		}
		int my_out = -1;
		if (!is_directed[i][c] && Query(vi{i, a, b}) == 1) my_out = c; else
		if (!is_directed[i][a] && Query(vi{i, b, c}) == 1) my_out = a; else
			my_out = b;
		is_directed[i][my_out] = true;
		is_directed[my_out][i] = true;
	}
	for (int i=1; i<=2*n; ++i) for (int j:graph[i]) {
		if (i<j && !is_directed[i][j]) {
			Answer(i, j);
		}
	}
}
