#include <vector>
#include <map>
#include <utility>
using namespace std;
using pp=pair<int,int>;

void InitMap(int N, int M);
void MakeMap(int A, int B);

namespace BOB {
int deg[1500];
bool ee[1500][1500]; // edge exist?
vector<pp> oe;       // original edges
bool iso[1500];      // is original?
int om[1500];        // original number

vector<int> be[1500]; // bit edges
map<pp, int> fp;      // fingerprints: (depth, maxdepth)
int dfs(int x, int p, int d) {
	int mxd = d;
	for (int y:be[x]) if (y != p) {
		int tmp = dfs(y, x, d+1);
		if (mxd < tmp) mxd = tmp;
	}
	fp[{d, mxd}] = x;
	return mxd;
}

void Bob(int n, int m, int a[], int b[]) {
	for (int i=0; i<m; ++i) {
		++deg[a[i]]; ++deg[b[i]];

		ee[a[i]][b[i]] = ee[b[i]][a[i]] = true;
	}

	int X, Y;
	for (X=0; X<n; ++X) if (deg[X] == n-2) break;
	for (Y=0; Y<n; ++Y) if (X!=Y && !ee[X][Y]) break;

	static int bv[20], bvn = 0;
	for (int i=0; i<n; ++i) if (ee[i][Y]) bv[bvn++] = i;

	for (int i=0; i<bvn; ++i) { int ba = bv[i];
		for (int j=0; j<bvn; ++j) { int bb = bv[j];
			if (ee[ba][bb]) be[ba].push_back(bb);
		}
	}

	//    -- 1 -- 2
	//   /
	//  0 -- 3 -- 4 -- 5
	//   \
	//    -- 6 -- 7 -- 8 -- 9

	int rt; // root
	for(rt=0; rt<bvn; ++rt) if (be[bv[rt]].size() == 3lu) break;
	rt = bv[rt];
	dfs(rt, -1, 0);

	int bf[10]; // bits found
	pp bffp[10] = {
		{0, 4},
		{1, 2}, {2, 2},
		{1, 3}, {2, 3}, {3, 3},
		{1, 4}, {2, 4}, {3, 4}, {4, 4}
	}; // bit fingerprints
	for (int i=0; i<10; ++i) bf[i] = fp[bffp[i]];
	for (int i=0; i<n; ++i) if (i!=X && i!=Y && be[i].empty()) {
		iso[i] = true;
		for (int j=0; j<10; ++j) if (ee[i][bf[j]]) om[i] += (1<<j);
	}

	for (int i=0; i<n; ++i) if (iso[i]) {
		for (int j=0; j<i; ++j) if (iso[j] && ee[i][j]) {
			oe.emplace_back(om[i], om[j]);
		}
	}

	InitMap(n-12, int(oe.size()));
	for (auto [x, y]: oe) {
		MakeMap(x, y);
	}
}
}

void Bob(int V, int U, int C[], int D[]) { BOB::Bob(V, U, C, D); }
