#include <iostream>
#include <vector>
#define pb push_back
using namespace std;
#define rep(i, n) for(int i=0; i<n; ++i)
#define rrep(i, n) for(int i=1; i<=n; ++i)
#define sz(v) ((int)((v).size()))

int nn;
vector<int> edge[2010];

int dp[2010][2010];
int ts[2010][2010];
int sz[2010];

char type[2010];
char buf[5010];
int rt()
{
	static int stk[1010], top;
	top = 0;
	for(int i=0; buf[i]; ++i) {
		if (buf[i] == '(') {
			stk[top++] = ++nn;
			if (top >= 2)
				edge[stk[top-2]].pb(nn);
		} else if (buf[i] == ')') {
			--top;
		} else type[stk[top-1]] = buf[i];
	}
	return stk[0];
}

void dfs(int x)
{
	sz[x] = 1;
	for(int y:edge[x]) dfs(y), sz[x] += sz[y];
}

int nt;
int F(int a, int b)
{
	int &ret = dp[a][b];
	if (ts[a][b] == nt) return ret;
	ts[a][b] = nt;

	ret = sz[a] + sz[b] - 2 + (type[a] != type[b]);

	auto &ca = edge[a], &cb = edge[b];
	int da = sz(ca), db = sz(cb);

	int t[db+1];

	t[0] = 0;
	for (int j=1; j<=db; ++j) t[j] = t[j-1]+sz[cb[j-1]];

	for (int i=1; i<=da; ++i) {
		int bt = t[0];
		t[0] += sz[ca[i-1]];
		for(int j=1; j<=db; ++j) {
			int nt = t[j-1]+sz[cb[j-1]];
			nt = min(nt, bt+F(ca[i-1], cb[j-1]));
			nt = min(nt, t[j]+sz[ca[i-1]]);
			bt = t[j];
			t[j] = nt;
		}
	}

	ret = min(ret, (type[a]!=type[b]) + t[db]);
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int tc; cin >> tc;
for(;tc--;) {
	++nt;
	rrep(i, nn) edge[i].clear(); nn = 0;
	cin >> buf; int ra = rt();
	cin >> buf; int rb = rt();
	dfs(ra); dfs(rb);
	cout << F(ra, rb) << '\n';
}
	return 0;
}
