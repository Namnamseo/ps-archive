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

const int maxn = int(3e5) + 10;

int n;

char s[maxn];

int pl[maxn], pr[maxn];

int nn;
int my[maxn];
pp lr[maxn];

auto single = [&](int i){ return (lr[i].y != lr[i].x+1) + 1; };

vector<int> ch[maxn];
vector<int> cb[maxn];

stack<int> S;

int dep[maxn];
int par[20][maxn];
int ci[maxn];
void dfs(int x) {
	int cc = 0;
	for(int y:ch[x]) {
		dep[y] = dep[x] + 1;
		par[0][y] = x;
		ci[y] = ++cc;
		dfs(y);
	}
}

int lca(int a, int b) {
	if(dep[a] > dep[b]) swap(b, a);
	int df = dep[b]-dep[a];
	for(int i=18; 0<=i; --i) if(1& (df>>i)) b=par[i][b];
	for(int i=18; 0<=i; --i) if(par[i][a] != par[i][b])
		a=par[i][a], b=par[i][b];
	if(a!=b) a=par[0][a];
	return a;
}

int pdst[20][maxn][2][2];

int q;

int ances(int snd, int spos, int tnd, int tpos) {
	int df = dep[snd] - dep[tnd];

	int dp[2] = {0, 0};
	dp[1-spos] = single(snd);

	for(int i=18; 0<=i; --i) if(1&(df>>i)) {
		int tdp[2] = {int(1e9), int(1e9)};
		rep(sp, 2) rep(tp, 2) {
			tdp[tp] = min(tdp[tp],
				dp[sp] + pdst[i][snd][sp][tp]);
		}
		dp[0] = tdp[0];
		dp[1] = tdp[1];
		snd = par[i][snd];
	}

	return dp[tpos];
}

int sib(int snd, int spos, int tnd, int tpos) {
	int va = 2*(ci[snd]-1)+spos;
	int vb = 2*(ci[tnd]-1)+tpos;
	int p = par[0][snd];
	if(va > vb) swap(va, vb);
	return cb[p][vb]-cb[p][va];
}

int calc(int snd, int spos, int tnd, int tpos) {
	int L = lca(snd, tnd);
	int ret = 1e9;
	// case 1
	if(L != 1) {
		rep(i, 2) rep(j, 2) ret = min(ret,
			ances(snd, spos, L, i) +
			ances(tnd, tpos, L, j) +
			(i != j ? 2 : 0)
			);
	}

	// case 2
	if(snd != L && tnd != L) {
		auto getbef = [&](int v, int bef) {
			int df = dep[v]-dep[bef]-1;
			for(int i=18; 0<=i; --i) if(1&(df>>i)) v=par[i][v];
			return v;
		};
		int bs = getbef(snd, L), bt = getbef(tnd, L);
		rep(sp, 2) rep(tp, 2) {
			ret = min(ret,
				ances(snd, spos, bs, sp) + 
				ances(tnd, tpos, bt, tp) + 
				sib(bs, sp, bt, tp)
			);
		}
	}

	return ret;
}

int main()
{
	cppio();
	cin >> n >> q;
	cin >> (s+1);

	rrep(i, n) { pl[i] = pl[i-1]; if(s[i] != '.') pl[i] = i; }
	pr[n] = n+1; for(int i=n; 1<=i; --i) { pr[i] = pr[i+1]; if(s[i] != '.') pr[i] = i; }

	S.push(1); nn = 1 ;
	rrep(i, n) if(s[i] != '.') {
		if(s[i] == '(') {
			int me = ++nn;
			my[i] = me; lr[me].x = i;
			if(S.size()) {
				ch[S.top()].pb(me);
			}
			S.push(me);
		} else {
			int me = S.top(); S.pop();
			lr[me].y = i; my[i] = me;
		}
	}

	dfs(1);
	rrep(i, nn) {
		int s = sz(ch[i]);
		if(!s) continue;

		cb[i].pb(lr[ch[i][0]].x-lr[i].x);
		rep(j, s) {
			if(j) cb[i].pb(lr[ch[i][j]].x-lr[ch[i][j-1]].y);
			int a = ch[i][j];
			cb[i].pb(single(a));
		}
		cb[i].pb(lr[i].y-lr[ch[i].back()].y);

		s = sz(cb[i]);
		for(int j=1; j<s; ++j) cb[i][j] += cb[i][j-1];
	}

	rrep(i, nn) {
		if(i == 1) continue;
		pdst[0][i][0][0] = cb[par[0][i]][2*(ci[i]-1)];
		pdst[0][i][0][1] = cb[par[0][i]].back() - pdst[0][i][0][0];

		pdst[0][i][1][0] = cb[par[0][i]][2*ci[i]-1];
		pdst[0][i][1][1] = cb[par[0][i]].back() - pdst[0][i][1][0];
	}

	for(int i=1; i<=18; ++i) {
		rrep(j, nn) par[i][j] = par[i-1][par[i-1][j]];
		rrep(j, nn) rep(sp, 2) rep(tp, 2) {
			pdst[i][j][sp][tp] = 1e9;
			rep(mp, 2) pdst[i][j][sp][tp] = min(pdst[i][j][sp][tp],
				pdst[i-1][j][sp][mp] + pdst[i-1][par[i-1][j]][mp][tp]);
		}
	}

	for(;q--;) {
		int a, b; cin >> a >> b;
		int ans = abs(a-b);
		for(int S:{pl[a], pr[a]}) if(S != 0 && S != n+1) for(int T:{pl[b], pr[b]}) if(T != 0 && T != n+1) {
			int nv = calc(my[S], (s[S] == ')'), my[T], (s[T] == ')')) +
				abs(a-S) + abs(b-T);
			ans = min(ans, nv);
		}
		cout << ans << '\n';
	}

	return 0;
}
