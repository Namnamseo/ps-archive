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

int n, m, t;
vector<pp> e[10010];

ll d[10010];
int bef[10010];
int be[10010];
int cc[10010];

vector<int> te[10010];
const ll inf = 1ll<<60;

ll ans;

void dfs(int x){
	for(int y:te[x]) dfs(y), cc[x] += cc[y];
	if(d[x] > t) ans = max(ans, (d[x] - t) * cc[x]);
}

int main()
{
	cppio();
	cin >> n >> m >> t;
	rrep(i, n) cin >> i[cc];
	rep(i, m){
		int a, b, c; cin >> a >> b >> c;
		e[a].eb(b, c); e[b].eb(a, c);
	}

	priority_queue<pll> pq;
	fill(d+2, d+n+1, inf);
	pq.emplace(0, 1);
	while(pq.size()){
		ll cd, x; tie(cd, x) = pq.top(); pq.pop(); cd = -cd;
		if(d[x] != cd) continue;
		for(auto tmp:e[x]){
			int y, ed; tie(y, ed) = tmp;
			ll nd = d[x] + ed;
			if(d[y] > nd){
				d[y] = nd;
				bef[y] = x;
				be[y] = ed;
				pq.emplace(-d[y], y);
			} else if(d[y] == nd && bef[y] > x){
				bef[y] = x;
				be[y] = ed;
			}
		}
	}

	for(int i=2; i<=n; ++i) te[bef[i]].pb(i);

	dfs(1);

	cout << ans << endl;
	return 0;
}

