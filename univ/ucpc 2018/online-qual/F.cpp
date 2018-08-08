#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second

struct MST{
	static const int M = 262144;
	vector<int> ys[M<<1];
	
	void add_p(int x, int y){
		for(x += M; x; x /= 2) ys[x].pb(y);
	}
	
	void init(){
		for(int i=0; i<(M*2); ++i) sort(all(ys[i]));
	}
	
	int cnt(vector<int>& v, int d, int u){
		return upper_bound(all(v), u) - lower_bound(all(v), d);
	}
	int rsum(int l, int r, int d, int u){
		int ret = 0;
		for(l+=M, r+=M; l<=r; l/=2, r/=2){
			if(l%2==1) ret += cnt(ys[l++], d, u);
			if(r%2==0) ret += cnt(ys[r--], d, u);
		}
		return ret;
	}
} mst;

int In[200010];
int Out[200010];
int mc[200010];

int n, m, c;

vector<int> edge[200010];
int par[200010];

int nt;
void dfs(int x){
	In[x] = ++nt;
	for(int y:edge[x]){
		if(y == par[x])continue;
		par[y]=x;
		dfs(y);
	}
	Out[x] = nt;
}

int main()
{
	read(n, m, c);
	for(int i=1; i<=n; ++i){
		read(mc[i]);
	}
	for(int i=1; i<n; ++i){
		int a, b; read(a, b);
		edge[a].pb(b);
		edge[b].pb(a);
	}
	dfs(1);
	for(int i=1; i<=n; ++i){
		mst.add_p(In[i], mc[i]);
	}
	mst.init();
	ll ans = 0;
	const ll mod = int(1e9)+7;
	for(;m--;){
		int v, c; read(v, c);
		(ans += mst.rsum(In[v], Out[v], 1, c)) %= mod;
	}
	printf("%lld\n", ans);
	return 0;
}
