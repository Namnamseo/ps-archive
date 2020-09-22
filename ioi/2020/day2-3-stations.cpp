#include <vector>
#include <algorithm>
using namespace std;

vector<int> edges[1010];
int n;

vector<int> dfs(int x, int p, int d)
{
	vector<int> cv;
	for(int y:edges[x]) if (y != p) {
		auto tmp = dfs(y, x, d+1);
		cv.insert(cv.end(), tmp.begin(), tmp.end());
	}
	if (d%2 == 0) cv.insert(cv.begin(), x);
	else cv.insert(cv.end(), x);

	return cv;
}

vector<int> label(int n_, int k, vector<int> u, vector<int> v)
{
	n = n_;
	for(int i=0; i<n; ++i) edges[i].clear();

	for(int i=0; i<n-1; ++i) {
		int a = u[i], b = v[i];
		edges[a].push_back(b);
		edges[b].push_back(a);
	}

	auto eu = dfs(0, -1, 0);

	vector<int> lbl(n);
	for(int i=0; i<n; ++i) lbl[eu[i]] = i;

	return lbl;
}

int find_next_station(int s, int t, vector<int> c)
{
	if (c.size() == 1u) return c[0];

	if (s > c[0]) {
		int sz = int(c.size()) - 1;
		c.push_back(s);
		for(int i=1; i<=sz; ++i) {
			int l = c[i], r = c[i+1]-1;
			if (l <= t && t <= r) return c[i];
		}
		return c[0];
	} else {
		rotate(c.begin(), c.end()-1, c.end());
		int sz = int(c.size()) - 1;
		c.insert(c.begin()+1, s);
		for(int i=2; i<=sz+1; ++i) {
			int r = c[i], l = c[i-1]+1;
			if (l <= t && t <= r) return c[i];
		}
		return c[0];
	}
}
