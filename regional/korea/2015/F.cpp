#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void cppio(){ ios_base::sync_with_stdio(0); cin.tie(0); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define sz(x) (int)(x).size()

int n, m;

const int maxn = int(1e5) + 10;
vector<int> e[maxn];

int idx[maxn], nt;
int low[maxn];
bitset<maxn> os;
int mys[maxn], sn;
int stk[maxn*2], top;
int col[maxn], par[maxn];
void color(int x, int s) {
	for(int y:e[x]) if (mys[y] == s) {
		if (col[y] && col[y] == col[x]) {
			static queue<int> q;
			q.push(y); par[y] = x;
			while (q.size()) {
				int a = q.front(); q.pop();
				for(int b:e[a]) if (mys[b] == s && !par[b] && col[b] && col[b] != col[a]) {
					par[b] = a;
					q.push(b);
				}
			}
			static vector<int> tmp; tmp.clear();
			for(int a=x;;a=par[a]) {
				tmp.pb(a); if (a == y) break;
			}
			cout << "1\n" << tmp.size() << '\n';
			for(int i=sz(tmp); i--;) cout << tmp[i] << '\n';
			throw 1;
		} else if (col[y]) continue;
		col[y] = col[x]^1;
		color(y, s);
	}
}

void dfs(int x) {
	idx[x] = low[x] = ++nt; os[x] = 1; stk[top++] = x;

	for(int y:e[x])
		if (!idx[y]) { dfs(y); low[x] = min(low[x], low[y]); }
		else if (os[y]) low[x] = min(low[x], idx[y]);

	if (idx[x] != low[x]) return;

	++sn;
	for(;top--;) {
		int a = stk[top];
		mys[a] = sn; os[a] = 0;
		if (a == x) break;
	}

	col[x] = 2;
	color(x, sn);
}

int main()
{
	cppio();
int tc; cin >> tc;
for(;tc--;) {
	cin >> n >> m;
	rep(i, m) { int a, b; cin >> a >> b; e[a].pb(b); }
	nt = 0; sn = 0;
	try {
		rrep(i, n) if (!idx[i]) dfs(i);
		throw 0;
	} catch (int t) {
		if (!t) {
			cout << "-1\n";
		}
	}
	fill(col+1, col+n+1, 0);
	fill(par+1, par+n+1, 0);
	fill(mys+1, mys+n+1, 0);
	fill(idx+1, idx+n+1, 0);
	rrep(i, n) e[i].clear();
	top = 0; os.reset();
}
	return 0;
}
