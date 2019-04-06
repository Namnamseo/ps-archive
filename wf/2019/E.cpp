#include <bits/stdc++.h>
using namespace std;
using pp=pair<int,int>;
#define x first
#define y second
#define rrep(i, n) for(int i=1; i<=n; ++i)
#define pb push_back
#define eb emplace_back

const int maxn = int(5e5) + 10;

int n, m;
pp e[maxn];
int par[maxn];
int vc[maxn], ec[maxn];
vector<int> my[maxn];
vector<pp> ans;
int deg[maxn];
vector<int> g[maxn];
vector<int> tmp[maxn];

int root(int x){ return (x==par[x])?x:(par[x]=root(par[x])); }

int main(){ ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> n >> m;
	iota(par+1, par+n+1, 1);
	rrep(i, m){
		int a, b; cin >> a >> b;
		e[i] = {a, b};
		++deg[a]; ++deg[b];
		g[a].pb(b); g[b].pb(a);
		par[root(a)] = root(b);
	}

	rrep(i, n) ++vc[root(i)], my[root(i)].pb(i);
	rrep(i, m) ++ec[root(e[i].x)];

	rrep(i, n) if(par[i] == i){
		if(ec[i] < vc[i]){
			for(int x:my[i]) if(deg[x] == 1){
				ans.eb(x, g[x][0]);
			}
			continue;
		}
		queue<int> q;

		for(int x:my[i]) if(deg[x] == 1) q.push(x);
		while(q.size()){
			int x=q.front(); q.pop();
			for(int y:g[x]) if(deg[y]){
				--deg[x]; --deg[y];
				tmp[x].clear(); tmp[y].pb(x);
				if(deg[y]==1) q.push(y);
			}
		}
		for(int x:my[i]) for(int y:tmp[x])
			ans.eb(x, y);
	}

	sort(ans.begin(), ans.end());
	cout << ans.size() << '\n';
	for(auto tmp:ans) cout << tmp.x << ' ' << tmp.y << '\n';

	return 0;
}
