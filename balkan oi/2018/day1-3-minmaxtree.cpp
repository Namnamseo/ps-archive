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

const int maxn = 70010;
vector<int> cond[maxn];
vector<int> delh[maxn];
vector<int> e[maxn];

int n;
int par[17][maxn];
int dep[maxn];

void dfs(int x){ for(int y:e[x]) if(par[0][x] != y){ par[0][y] = x; dep[y]=dep[x]+1; dfs(y); } }
int lca(int a, int b){
	if(dep[a] > dep[b]) swap(a, b);
	for(int i=16; 0<=i; --i) if(1&((dep[b]-dep[a])>>i)) b=par[i][b];
	if(a==b) return a;
	for(int i=16; 0<=i; --i) if(par[i][a] != par[i][b]) a=par[i][a], b=par[i][b];
	return par[0][a];
}

int ct[maxn];
int cv[maxn];
pp pe[maxn];

multiset<int> lb[maxn], ub[maxn];

void solve(int x){
	auto &L=lb[x], &U=ub[x];
	for(int y:e[x]) if(par[0][y] == x){
		solve(y);
		if(L.size()+U.size() < lb[y].size()+ub[y].size()){
			swap(L, lb[y]);
			swap(U, ub[y]);
		}
		L.insert(all(lb[y])); lb[y].clear();
		U.insert(all(ub[y])); ub[y].clear();
	}

	for(int c:cond[x]){
		if(ct[c] == 0) L.insert(cv[c]);
		else U.insert(cv[c]);
	}

	pe[x] = {-1, -1};
	if(L.size()) pe[x].x = *--L.end();
	if(U.size()) pe[x].y = *U.begin();

	for(int c:delh[x]){
		if(ct[c] == 0) L.erase(L.find(cv[c]));
		else U.erase(U.find(cv[c]));
	}
}

namespace match {
	const int maxv = 70000 * 2 + 10;
	vector<int> e[maxv];
	int lev[maxv];
	int rev[maxv];
	int mat[maxv];

	void adde(int l, int r){
		e[l].pb(r);
	}

	void match(int n, int m){
	auto bfs = [&](){
		fill(lev+1, lev+n+m+1, -1);
		queue<int> q;
		rrep(i, n) if(!mat[i]){ lev[i]=0; q.push(i); }
		bool reach = 0;
		while(q.size()){
			int x=q.front(); q.pop();
			if(x > n){
				if(rev[x]){ lev[rev[x]] = lev[x]+1; q.push(rev[x]); }
				else reach = 1;
			} else for(int y:e[x]) if(!~lev[y]){
				lev[y] = lev[x]+1; q.push(y);
			}
		}
		return reach;
	};

		static bool vis[maxv];
	function<bool(int)> dfs = [&](int x){
		if(vis[x]) return 0;
		vis[x]=1;
		for(int y:e[x]) if(lev[y]==lev[x]+1){
			if(!rev[y]){
				rev[y]=x; mat[x]=y;
				return 1;
			} else if(lev[rev[y]] == lev[y]+1){
				if(dfs(rev[y])){
					rev[y]=x; mat[x]=y;
					return 1;
				}
			}
		}
		return 0;
	};

		while(bfs()){
			fill(vis+1, vis+n+1, 0);
			rrep(i, n) if(lev[i]==0 && !vis[i]) dfs(i);
		}
	}
};

map<int,int> rm;

int kp(int x, int k){
	for(int i=16; 0<=i; --i) if(1&(k>>i)) x=par[i][x];
	return x;
}

int main()
{
	int k;
[&](){
	cppio(); cin >> n;
	rep(i, n-1){ int a, b; cin >> a >> b; e[a].pb(b); e[b].pb(a); }

	dfs(1);
	rrep(i, 16) rrep(j, n) par[i][j] = par[i-1][par[i-1][j]];

	cin >> k;
	rrep(i, k){
		char cmd[5];
		int x, y, z;
		cin >> cmd >> x >> y >> z;
		int l = lca(x, y);
		if(l != x) cond[x].pb(i), delh[kp(x, dep[x]-dep[l]-1)].pb(i);
		if(l != y) cond[y].pb(i), delh[kp(y, dep[y]-dep[l]-1)].pb(i);

		ct[i] = (cmd[0] == 'M');
		cv[i] = z;

		rm[z] = i;
	}
}();

	solve(1);
	rrep(i, n) if(par[0][i]){
		int x, y; tie(x, y) = pe[i];
		if(~x) match::adde(rm[x], k+i);
		if(~y) match::adde(rm[y], k+i);
	}

	match::match(k, n);

	rrep(i, n) if(par[0][i]){
		int j = par[0][i];
		printf("%d %d ", i, j);
		if(match::rev[k+i]){
			printf("%d\n", cv[match::rev[k+i]]);
		} else {
			int a, b; tie(a, b) = pe[i];
			if(a != -1) printf("%d\n", a);
			else if(b != -1) printf("%d\n", b);
			else puts("1");
		}
	}

	return 0;
}
