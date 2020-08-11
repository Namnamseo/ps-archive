#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
void read(pp& x){ scanf("%d%d",&x.first, &x.second); }
void read(pll& x){ scanf("%lld%lld",&x.first, &x.second); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
void cppio(){ ios_base::sync_with_stdio(0); cin.tie(0); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define sz(x) (int)(x).size()

const int maxn = int(1e5) + 10;
const int maxq = int(1e5) + 10;

int n, m, k, q;
vector<pp> e[maxn];

vector<int> feast;

ll dist[maxn];
int dh[maxn], dhn;
void Dijkstra() {
	const ll inf = 1e9;
	priority_queue<pll> pq;
	fill(dist+1, dist+n+1, inf);
	for (int x:feast) { dist[x] = 0; pq.emplace(0, x); }
	while (pq.size()) {
		ll d; int x; tie(d, x) = pq.top(); pq.pop();
		d = -d;
		if (d != dist[x]) continue;
		dh[dhn++] = x;
		for (auto &tmp:e[x]) {
			int y; ll c; tie(y, c) = tmp;
			if (dist[y] > c+d) {
				dist[y] = c+d;
				pq.emplace(-dist[y], y);
			}
		}
	}
}

set<int> qs[maxn];
int ans[maxq];

int par[maxn];
int r(int x) { return (x==par[x]) ? x : (par[x]=r(par[x])); }
bitset<maxn> vis;

int main()
{
	cppio();
	cin >> n >> m >> k >> q;
	rrep(i, m) {
		int a, b, c; cin >> a >> b >> c;
		e[a].eb(b, c); e[b].eb(a, c);
	}
	feast.resize(k); for (int &x:feast) cin >> x;
	Dijkstra();

	rrep(i, q) {
		int a, b; cin >> a >> b;
		qs[a].insert(i);
		qs[b].insert(i);
	}

	iota(par+1, par+n+1, 1);
	for (int i=dhn-1; 0<=i; --i) {
		int x = dh[i];
		int dx = dist[x];
		vis[x] = 1;
		for (auto &tmp:e[x]) { int y = tmp.x;
			if (!vis[y]) continue;
			int a = r(x), b = r(y);
			if (a == b) continue;
			if (sz(qs[a]) > sz(qs[b])) swap(a, b);
			for (int qi:qs[a]) if (!qs[b].insert(qi).y) {
				ans[qi] = dx;
			}
			par[a] = b;
		}
	}

	rrep(i, q) cout << ans[i] << '\n';
	return 0;
}
