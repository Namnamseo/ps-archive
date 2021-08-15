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

int n;

bitset<30> e[30];

ll p[30] = {
	50956583, 21039143, 76181711, 45713621, 36065111, 4958801, 95156879, 89647573, 39628549, 45675941, 39054881, 79639267, 79327987, 3858493, 74819039, 19224521, 46903793, 22921783, 78664543, 69707857, 32838467, 57990727, 61983673, 20689481, 47599963, 22058761, 89409049, 5404831, 2035301, 40272719
};

ll mod = int(1e9) + 7;

int nt;
int dfs(int x, int p=-1, int dep=0) {
	static int memo[30][31][30];
	static int memt[30][31][30];
	if (memt[x][p+1][dep] == nt) return memo[x][p+1][dep];
	memt[x][p+1][dep] = nt; int &ret = memo[x][p+1][dep]; ret = 0;
	vector<int> tmp;
	rep(y, n) if (y != p && e[x][y]) tmp.push_back(dfs(y, x, dep+1));
	sort(all(tmp));
	for (int i=0, s=tmp.size(); i<s; ++i) {
		ll v = tmp[i]; v *= (i+1); v %= mod;
		v ^= (::p)[dep];
		ret = (ret+v)%mod;
	}
	return ret;
}

int deg[30];
int degcnt[30];
vector<int> get_hashes() {
	memset(deg, 0, sizeof(int)*n);
	memset(degcnt, 0, sizeof(int)*n);

	rep(i, n) rep(j, i) if (e[i][j]) ++deg[i], ++deg[j];
	vector<int> v;
	rep(i, n) rep(j, i) if (e[i][j]) {
		int a = deg[i], b = deg[j];
		if (a > b) swap(a, b);
		v.push_back(a*(n-1)+b);
	}
	sort(all(v));

	rep(i, n) {
		++degcnt[deg[i]];
	}

	++nt;

	for (int lev=1; lev<=n; ++lev) {
		rrep(i, n-1) if (degcnt[i] == lev) {
			int t = 0;
			rep(j, n) if (deg[j] == i) {
				v.push_back(dfs(j));
				++t;
			}
			sort(v.end()-t, v.end());
			return v;
		}
	}

	return v;
}

vector<vector<int>> S[31];

int main()
{
	cppio();

	int t;
	cin >> t;
	for (;t--;) {
		cin >> n;
		for (int i=1; i<n; ++i) {
			int x, y; cin >> x >> y;
			e[x][y] = e[y][x] = 1;
		}

		auto H = get_hashes();
		S[n].eb(H);

		rep(i, n) e[i].reset();
	}

	int ans = 0;
	rrep(s, 30) {
		auto &T = S[s];
		sort(all(T));
		ans += unique(all(T)) - T.begin();
	}

	cout << ans << endl;
	return 0;
}
