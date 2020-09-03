#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pp;
typedef long long ll;
#define all(x) (x).begin(),(x).end()
#define pb push_back
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args> void read(T& a,Args&... b){ read(a); read(b...); }

const int max_n = 200010;
const ll inf = 1LL<<60;

vector<pp> edge[max_n];
map<pp, int> ed;
int par[max_n];

ll   dp [max_n][3][2];
bool chk[max_n][3][2];

int n;

void in(){
	read(n);
	for(int i=1; i<n; ++i){
		int x, y, d; read(x, y, d);
		edge[x].pb({y, d});
		edge[y].pb({x, d});
		ed[{x, y}] = d;
		ed[{y, x}] = d;
	}
}

vector<int> nin[max_n];
ll osum[max_n];
multiset<ll> mev[max_n];

void dfs(int x){
	for(pp tmp:edge[x]){
		int y=tmp.first;
		if(par[x]!=y) par[y]=x, nin[x].pb(y), dfs(y);
	}
	if(par[x]) nin[x].pb(par[x]);
}

ll f(int, int, int);

int vc[max_n];
int lf[max_n];
int ld[max_n];

void fill_val(int p, int from){
	if(lf[p] == from) return;
	if(vc[p] == 0){
		for(pp tmp:edge[p]){
			int x, dst;
			tie(x, dst)=tmp;
			if(x == from){
				ld[p]=dst;
				continue;
			}
			ll ov = max(f(x, p, 0), dst + f(x, p, 1));
			osum[p] += ov;
			mev[p].insert(dst + f(x, p, 0) - ov);
		}
	} else {
		if(lf[p] != -1){
			int x=lf[p], dst=ld[p];
			ll ov = max(f(x, p, 0), dst + f(x, p, 1));
			osum[p] += ov;
			mev[p].insert(dst + f(x, p, 0) - ov);
		}
		if(from != -1){
			int x=from, dst=ed[pp{from, p}];
			ll ov = max(f(x, p, 0), dst + f(x, p, 1));
			osum[p] -= ov;
			mev[p].erase(mev[p].find(dst + f(x, p, 0) - ov));
			ld[p]=dst;
		}
	}
	++vc[p];
	lf[p]=from;
}

ll f(int p, int from, int parity){
	int child=(from == -1) ? p : (par[from]==p ? from:p);
	int sec = (from == -1) ? 2 : (p==child);
	ll& mydp = dp[child][sec][parity];
	if(chk[child][sec][parity]) return mydp;
	chk[child][sec][parity]=1;
	mydp = -inf;
    
	fill_val(p, from);
	if(parity == 0){
		mydp = osum[p];
	} else {
		if(mev[p].size())
			mydp = osum[p] + *--mev[p].end();
	}
	
	return mydp;
}

int main()
{
	in(); dfs(1);
	ll ans = 0;
	for(int i=1; i<=n; ++i){
		multiset<ll> diff;
		for(auto tmp:edge[i]){
			int y, d; tie(y, d) = tmp;
			ll v = d+f(y, i, 0);
			v -= max(f(y, i, 0), d+f(y, i, 1));
			diff.insert(v);
			if(diff.size() == 3u) diff.erase(diff.begin());
		}
		ll mv = f(i, -1, 0);
		ans = max(ans, mv);
		if(diff.size() >= 2u){
			auto it=diff.rbegin();
			auto i2=it; ++i2;
			ans = max(ans, mv + *it + *i2);
		}
	}
	printf("%lld\n", ans);
	return 0;
}

