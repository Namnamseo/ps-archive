#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define sz(x) (int)(x).size()

int n, k;

vector<int> e[100010];
int p[100010];
int dep[100010];

int both[100010];
int maxd[100001];
int secd[100001];
int tri[100001];
int four[100001];

void dfs(int x){
	maxd[x] = dep[x];
	secd[x] = -1;
	for(int y:e[x]){
		if(y == p[x]) continue;
		p[y] = x;
		dep[y] = dep[x]+1;
		dfs(y);

		four[x] = max({four[x], four[y],
			maxd[x] + tri[y] - 2*dep[x],
			maxd[y] + tri[x] - 2*dep[x],
			both[x] + both[y]});

		tri[x] = max({tri[x], maxd[x]+both[y], both[x]+maxd[y], tri[y]});

		both[x] = max({both[x], both[y], maxd[x]+maxd[y]-2*dep[x]});
		maxd[x] = max(maxd[x], maxd[y]);
	}
}

namespace k1 {
	void solve(){
		printf("%d\n", 2*(n-1) - both[1] + 1);
	}
}

namespace k2 {
	void solve(){
		printf("%d\n", 2*(n-1) + 2 - four[1]);
	}
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	for(int i=1; i<n; ++i){
		int a, b; cin >> a >> b;
		e[a].pb(b); e[b].pb(a);
	}
	dfs(1);
	if(k == 1) k1::solve();
	else k2::solve();
	return 0;
}
